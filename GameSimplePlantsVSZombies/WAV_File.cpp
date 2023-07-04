#include "WAV_File.h"
#include <array>
#include <SDL_log.h>

bool WAV_File::Open(std::string filePath)
{
	//����Ѿ����ļ����ȹر�
	if (fdata.is_open())
		fdata.close();

	//ͨ�����·������Ƶ�ļ���
	fdata.clear();
	fdata.open(filePath, std::ios::in | std::ios::binary);	//��������ö����Ʋ���������ᵼ�����ݶ�������

	//�ļ��򿪳ɹ�
	if (fdata.is_open())
	{
		//�ļ�ͷ
		file_header fileHeader;

		//��ȡ�ļ�ͷ
		fdata.read((char*)&fileHeader, 36);

		//������Ƶ��Ϣ
		//���ļ�·���н�ȡ��Ƶ�ļ���
		int i = filePath.find_last_of('/');
		mFileName = filePath.substr(i + 1, filePath.size() - 1);
		//��ȡ�ļ���С
		mFileSize = fileHeader.chunkSize + 8;
		//��ȡ������
		mAudioSampleRate = fileHeader.sampleRate;
		//��Ƶ������
		mAudioChannels = fileHeader.numChannels;
		//��Ƶ���ݸ�ʽ��λ��8λ��16λ��
		mBitsPerSample = fileHeader.bitsPerSample;

		// Ѱ�ҡ�data����
		std::string chunkID("1234");
		uint32_t chunkSize;
		std::streampos dataStart;
		do
		{
			fdata.read(reinterpret_cast<char*>(chunkID.data()), 4);
			fdata.read(reinterpret_cast<char*>(&chunkSize), 4);
			dataStart = fdata.tellg();
			fdata.seekg(chunkSize, std::ios::cur);
		} while (chunkID != "data");
		// ��Ƶ���ݿ�ʼλ��
		mAudioDataBegin = dataStart;
		//��Ƶ���ݴ�С = ���ļ���С - �ļ�ͷ��С
		mAudioDataSize = chunkSize;

		// ��ȡ��Ƶ����
		mAudioData.clear();
		mAudioData.resize(mAudioDataSize);
		//��λ����Ƶ���ݵ���ʼλ��
		fdata.seekg(mAudioDataBegin);
		//��ȡ������Ƶ���ݵ�����
		fdata.read((char*)mAudioData.data(), mAudioDataSize);

		return true;
	}

	//�ļ���ʧ�ܷ���false
	SDL_Log(u8"Wav��Ƶ��ʧ��");
	return false;
}

std::vector<uint8_t>& WAV_File::GetAudioData()
{
	return mAudioData;
}

WAV_File::WAV_File(std::string filePath)
{
	Open(filePath);
}

WAV_File::~WAV_File()
{
	//����Ѿ����ļ����ȹر�
	if (fdata.is_open())
		fdata.close();
}
