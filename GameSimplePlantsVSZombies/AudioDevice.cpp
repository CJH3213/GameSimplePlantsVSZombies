#include "AudioDevice.h"
#include <SDL_assert.h>
#include <SDL_log.h>
#include <iterator>

void AudioDevice::Open()
{
	auto& ins = GetInstance();

	if (ins.mIsOpened == true)
	{
		SDL_CloseAudio();
	}

	// ���������Ĳ��Ų���
	ins.mDesiredSpec.freq = 44100;	// ������ ÿ��
	ins.mDesiredSpec.format = AUDIO_S16;	//������ʽ��Ĭ��PCM�з���ʽ | λ��
	ins.mDesiredSpec.channels = 2;		// ����
	ins.mDesiredSpec.silence = 0;	// ����ֵ����������Ƶ���ݵ�ʱ���ȡֵ��
	ins.mDesiredSpec.samples = 1024;	// ÿͨ�����������ٴ�С������ռ�ռ䣬С��Ƶ���ص�
	// size = samples * channels * (bits per sample / 8)
	ins.mDesiredSpec.callback = AudioCallback;
	ins.mDesiredSpec.userdata = &ins;		//����ǰ������Ϊ�û����ݴ���

	// ������ڶ���������ֵ������Ҫ�ֶ�ת�룬����û������ 
	//SDL_PauseAudio(1);
	int res = SDL_OpenAudio(&(ins.mDesiredSpec), NULL);
	SDL_PauseAudio(0);

	ins.mIsOpened = true;
}

void AudioDevice::Close()
{
	auto& ins = GetInstance();

	if (ins.mIsOpened == true)
	{
		SDL_CloseAudio();
	}
}

void AudioDevice::Play(AudioPackage* pack)
{
	auto& ins = GetInstance();
	auto& packs = ins.mAudioPackages;
	auto& desiredSpec = ins.mDesiredSpec;


	auto it = std::find(packs.begin(), packs.end(), pack);
	// �Ѿ����ڣ���Ҫ�ظ����
	if (it != packs.end())
		return;		

	// δ���ڣ������Ƶ������
	// �Ƚ���Ƶ�Ͳ�������ʽ������ͬ����Ҫת��
	if (pack->mDesiredSpec.freq != desiredSpec.freq ||
		pack->mDesiredSpec.format != desiredSpec.format ||
		pack->mDesiredSpec.channels != desiredSpec.channels)
	{
		SDL_AudioCVT cvt;
		SDL_BuildAudioCVT(&cvt, 
			pack->mDesiredSpec.format, pack->mDesiredSpec.channels, pack->mDesiredSpec.freq,
			desiredSpec.format, desiredSpec.channels, desiredSpec.freq);

		SDL_assert(cvt.needed);
		cvt.len = pack->mData.size();		// Դ���ݴ�С
		pack->mData.resize(cvt.len * cvt.len_mult);	// Ԥ����������С = ԭ��С * �������
		cvt.buf = pack->mData.data();	// ���뻺���������Ƚ�ԭ���ݸ��Ƶ���������ת��������ݽ��Ḳ��

		SDL_ConvertAudio(&cvt);
		pack->mData.resize(cvt.len * cvt.len_ratio);	// ת�������Ч�ֽ��� = ԭ��С * ���ű���
		pack->mDesiredSpec = desiredSpec;
	}

	// ��ӵ���Ƶ������
	std::lock_guard<std::mutex> lock(ins.mMutex);
	packs.emplace_back(pack);
}

void AudioDevice::Remove(AudioPackage* pack)
{
	auto& ins = GetInstance();
	auto& packs = ins.mAudioPackages;

	std::lock_guard<std::mutex> lock(ins.mMutex);

	auto it = std::find(packs.begin(), packs.end(), pack);
	if (it != packs.end())
		packs.erase(it);
}

AudioPackage* AudioDevice::LoadWav(std::string path)
{
	// ����WAV��Ƶ�ļ���Ϣ������
	SDL_AudioSpec audioSpec;
	uint8_t* buf = nullptr;
	uint32_t len = 0;
	auto res = SDL_LoadWAV(path.c_str(), &audioSpec, &buf, &len);

	// ��SDL��Ƶ���ݴ��ΪAudioPackage
	if (res == NULL)
	{
		SDL_Log(u8"WAV��Ƶ����ʧ�ܣ�%s", path.c_str());
		return nullptr;
	}

	AudioPackage* pack = new AudioPackage;
	pack->mDesiredSpec = audioSpec;
	pack->mData.resize(len);
	std::memcpy(pack->mData.data(), buf, len);

	// �ͷ�WAV���ص���Դ
	SDL_FreeWAV(buf);
	return pack;
}

AudioDevice::AudioDevice()
{
	SDL_zero(mDesiredSpec);
}

void AudioDevice::AudioCallback(void* userdata, uint8_t* stream, int len)
{
	//�ص������ֶ�������Ƶ��
	SDL_memset(stream, 0, len);

	AudioDevice* ins = (AudioDevice*)userdata;
	auto& packages = ins->mAudioPackages;

	std::lock_guard<std::mutex> lock(ins->mMutex);

	for (auto& pack : packages)
	{
		size_t dataLen = pack->mData.size();
		size_t currIndex = pack->mPlaybackProgress;

		// �����ǰ��Ƶ�����Ѿ�������ϣ��Ƿ�ѭ������
		if (currIndex >= dataLen)
			if (pack->mIsLoop == false)
				continue;
			else
				pack->mPlaybackProgress = 0;

		// ʣ���ֽ��Ƿ�С�ڻ�������С
		size_t remainingLen = dataLen - currIndex;
		size_t fillLen = len < remainingLen? len : remainingLen;

		// ������Ƶ����װ�ص���Ƶ��������
		SDL_MixAudio(stream, pack->mData.data() + currIndex, fillLen, 
			SDL_MIX_MAXVOLUME * pack->mVolume);

		// ��Ƶָ������
		currIndex += len;
		pack->mPlaybackProgress += fillLen;

		// ��ʾ��ǰ��Ƶ�Ľ���
		//SDL_Log(u8"���Ž��ȣ�%d", pack->mPlaybackProgress);
	}
}
