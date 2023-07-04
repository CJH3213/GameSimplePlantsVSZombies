#include "WAV_File.h"
#include <array>
#include <SDL_log.h>

bool WAV_File::Open(std::string filePath)
{
	//如果已经打开文件，先关闭
	if (fdata.is_open())
		fdata.close();

	//通过相对路径打开音频文件流
	fdata.clear();
	fdata.open(filePath, std::ios::in | std::ios::binary);	//请务必设置二进制操作，否则会导致数据读不出来

	//文件打开成功
	if (fdata.is_open())
	{
		//文件头
		file_header fileHeader;

		//读取文件头
		fdata.read((char*)&fileHeader, 36);

		//解析音频信息
		//从文件路径中截取音频文件名
		int i = filePath.find_last_of('/');
		mFileName = filePath.substr(i + 1, filePath.size() - 1);
		//获取文件大小
		mFileSize = fileHeader.chunkSize + 8;
		//获取采样率
		mAudioSampleRate = fileHeader.sampleRate;
		//音频声道数
		mAudioChannels = fileHeader.numChannels;
		//音频数据格式（位宽：8位、16位）
		mBitsPerSample = fileHeader.bitsPerSample;

		// 寻找“data”块
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
		// 音频数据开始位置
		mAudioDataBegin = dataStart;
		//音频数据大小 = 总文件大小 - 文件头大小
		mAudioDataSize = chunkSize;

		// 获取音频数据
		mAudioData.clear();
		mAudioData.resize(mAudioDataSize);
		//定位到音频数据的起始位置
		fdata.seekg(mAudioDataBegin);
		//读取所有音频数据到数组
		fdata.read((char*)mAudioData.data(), mAudioDataSize);

		return true;
	}

	//文件打开失败返回false
	SDL_Log(u8"Wav音频打开失败");
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
	//如果已经打开文件，先关闭
	if (fdata.is_open())
		fdata.close();
}
