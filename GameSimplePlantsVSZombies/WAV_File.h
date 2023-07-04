#pragma once
#include <fstream>
#include <string>
#include <vector>

class WAV_File
{
private:

	// 可借助WinHex软件分析数据格式
	//WAV文件头信息：44字节，只读取前36字节
	struct file_header
	{
		//RIFF信息描述
		char chunkID[4];			//4字节，内容为“RIFF”
		uint32_t chunkSize;		//4字节，记录整个文件中format的字节数，单位bytes，总文件大小 = chunkSize + 4 + 4
		char format[4];			//4字节，内容为“WAVE”，标识文件是WAV文件块

		//音频信息
		char subChunk1ID[4];		//4字节，内容“fmt ”，FormatChunk的标记
		uint32_t subChunk1Size;	//4字节，文件块1的大小，若无扩展块则为16，有扩展块则值为 = 16 + 2字节扩展块长度 + 扩展块长度

		//2字节：音频格式：
		//0x0001：PCM、
		//0x0003：存放IEEE float [-1.0f~1.0f]、
		//0x0006：A-law、
		//0x0007：u-law
		//0xFFFE：具体编码方式由扩展区subFormat字段决定
		uint16_t audioFormat;
		//2字节：声道数：1单声道、2双声道
		uint16_t numChannels;
		//4字节：采样率：8000、44100、等
		uint32_t sampleRate;
		//4字节：音频码率：采样率*声道数*位宽/8bit， 单位byte
		uint32_t byteRate;
		//2字节：每次采样大小：声道数*位宽/8bit，单位byte
		uint16_t blockAlign;
		//2字节：每次采样，每个通道样本大小，单位bit，除与8bit就是位宽
		uint16_t bitsPerSample;

		//uint16_t extraParamSize;		//扩展块大小
		//uint8_t*  extraParams			//扩展块数据

	//数据块
	//uint32_t subChunk2ID;		//4字节，内容为“data”
	//uint32_t subChunk2Size;	//4字节，数据总长度
	};

private:
	//文件流
	std::ifstream fdata;

	//文件名
	std::string mFileName = "";
	//文件大小
	uint32_t mFileSize = 0;
	//音频数据起始位置
	uint16_t mAudioDataBegin = 0;
	//音频数据大小
	uint32_t mAudioDataSize = 0;
	//音频采样率
	int mAudioSampleRate = 0;
	//音频数据格式（位宽：8位、16位）
	uint16_t mBitsPerSample = 0;
	//音频声道数
	uint16_t mAudioChannels = 0;

	// 所有音频数据
	std::vector<uint8_t> mAudioData;

public:

	//构造函数，传入文件路径
	WAV_File(std::string filePath);
	//析构
	~WAV_File();

	//打开文件（重新加载音频文件）
	bool Open(std::string filePath);

	// 获得采样率
	uint32_t GetSampleRate() const { return mAudioSampleRate; }
	// 获得采样位宽：8位、16位）
	uint8_t GetBitsPerSample() const { return mBitsPerSample; }
	// 获得声道数
	uint8_t GetChannels() const { return mAudioChannels; }
	// 获取音频数据引用
	std::vector<uint8_t>& GetAudioData();
};

