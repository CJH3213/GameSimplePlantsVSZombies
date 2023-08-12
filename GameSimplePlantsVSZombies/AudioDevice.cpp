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

	// 填入期望的播放参数
	ins.mDesiredSpec.freq = 44100;	// 采样数 每秒
	ins.mDesiredSpec.format = AUDIO_S16;	//采样格式：默认PCM有符格式 | 位宽
	ins.mDesiredSpec.channels = 2;		// 声道
	ins.mDesiredSpec.silence = 0;	// 静音值（对于无音频内容的时候的取值）
	ins.mDesiredSpec.samples = 1024;	// 每通道缓存区开辟大小，大了占空间，小了频繁回调
	// size = samples * channels * (bits per sample / 8)
	ins.mDesiredSpec.callback = AudioCallback;
	ins.mDesiredSpec.userdata = &ins;		//将当前对象作为用户数据传入

	// 如果给第二个参数赋值，就需要手动转码，否则没有声音 
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
	// 已经存在，不要重复添加
	if (it != packs.end())
		return;		

	// 未存在，添加音频到容器
	// 比较音频和播放器格式，不相同就需要转换
	if (pack->mDesiredSpec.freq != desiredSpec.freq ||
		pack->mDesiredSpec.format != desiredSpec.format ||
		pack->mDesiredSpec.channels != desiredSpec.channels)
	{
		SDL_AudioCVT cvt;
		SDL_BuildAudioCVT(&cvt, 
			pack->mDesiredSpec.format, pack->mDesiredSpec.channels, pack->mDesiredSpec.freq,
			desiredSpec.format, desiredSpec.channels, desiredSpec.freq);

		SDL_assert(cvt.needed);
		cvt.len = pack->mData.size();		// 源数据大小
		pack->mData.resize(cvt.len * cvt.len_mult);	// 预备缓存区大小 = 原大小 * 扩大比例
		cvt.buf = pack->mData.data();	// 传入缓存区，请先将原数据复制到缓存区，转换后的数据将会覆盖

		SDL_ConvertAudio(&cvt);
		pack->mData.resize(cvt.len * cvt.len_ratio);	// 转换后的有效字节数 = 原大小 * 缩放比率
		pack->mDesiredSpec = desiredSpec;
	}

	// 添加到音频包容器
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
	// 加载WAV音频文件信息和数据
	SDL_AudioSpec audioSpec;
	uint8_t* buf = nullptr;
	uint32_t len = 0;
	auto res = SDL_LoadWAV(path.c_str(), &audioSpec, &buf, &len);

	// 将SDL音频数据打包为AudioPackage
	if (res == NULL)
	{
		SDL_Log(u8"WAV音频加载失败：%s", path.c_str());
		return nullptr;
	}

	AudioPackage* pack = new AudioPackage;
	pack->mDesiredSpec = audioSpec;
	pack->mData.resize(len);
	std::memcpy(pack->mData.data(), buf, len);

	// 释放WAV加载的资源
	SDL_FreeWAV(buf);
	return pack;
}

AudioDevice::AudioDevice()
{
	SDL_zero(mDesiredSpec);
}

void AudioDevice::AudioCallback(void* userdata, uint8_t* stream, int len)
{
	//回调后先手动清零音频流
	SDL_memset(stream, 0, len);

	AudioDevice* ins = (AudioDevice*)userdata;
	auto& packages = ins->mAudioPackages;

	std::lock_guard<std::mutex> lock(ins->mMutex);

	for (auto& pack : packages)
	{
		size_t dataLen = pack->mData.size();
		size_t currIndex = pack->mPlaybackProgress;

		// 如果当前音频数据已经播放完毕，是否循环播放
		if (currIndex >= dataLen)
			if (pack->mIsLoop == false)
				continue;
			else
				pack->mPlaybackProgress = 0;

		// 剩余字节是否小于缓冲区大小
		size_t remainingLen = dataLen - currIndex;
		size_t fillLen = len < remainingLen? len : remainingLen;

		// 将新音频数据装载到音频流缓存区
		SDL_MixAudio(stream, pack->mData.data() + currIndex, fillLen, 
			SDL_MIX_MAXVOLUME * pack->mVolume);

		// 音频指针增长
		currIndex += len;
		pack->mPlaybackProgress += fillLen;

		// 显示当前音频的进度
		//SDL_Log(u8"播放进度：%d", pack->mPlaybackProgress);
	}
}
