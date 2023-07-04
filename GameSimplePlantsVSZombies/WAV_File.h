#pragma once
#include <fstream>
#include <string>
#include <vector>

class WAV_File
{
private:

	// �ɽ���WinHex����������ݸ�ʽ
	//WAV�ļ�ͷ��Ϣ��44�ֽڣ�ֻ��ȡǰ36�ֽ�
	struct file_header
	{
		//RIFF��Ϣ����
		char chunkID[4];			//4�ֽڣ�����Ϊ��RIFF��
		uint32_t chunkSize;		//4�ֽڣ���¼�����ļ���format���ֽ�������λbytes�����ļ���С = chunkSize + 4 + 4
		char format[4];			//4�ֽڣ�����Ϊ��WAVE������ʶ�ļ���WAV�ļ���

		//��Ƶ��Ϣ
		char subChunk1ID[4];		//4�ֽڣ����ݡ�fmt ����FormatChunk�ı��
		uint32_t subChunk1Size;	//4�ֽڣ��ļ���1�Ĵ�С��������չ����Ϊ16������չ����ֵΪ = 16 + 2�ֽ���չ�鳤�� + ��չ�鳤��

		//2�ֽڣ���Ƶ��ʽ��
		//0x0001��PCM��
		//0x0003�����IEEE float [-1.0f~1.0f]��
		//0x0006��A-law��
		//0x0007��u-law
		//0xFFFE��������뷽ʽ����չ��subFormat�ֶξ���
		uint16_t audioFormat;
		//2�ֽڣ���������1��������2˫����
		uint16_t numChannels;
		//4�ֽڣ������ʣ�8000��44100����
		uint32_t sampleRate;
		//4�ֽڣ���Ƶ���ʣ�������*������*λ��/8bit�� ��λbyte
		uint32_t byteRate;
		//2�ֽڣ�ÿ�β�����С��������*λ��/8bit����λbyte
		uint16_t blockAlign;
		//2�ֽڣ�ÿ�β�����ÿ��ͨ��������С����λbit������8bit����λ��
		uint16_t bitsPerSample;

		//uint16_t extraParamSize;		//��չ���С
		//uint8_t*  extraParams			//��չ������

	//���ݿ�
	//uint32_t subChunk2ID;		//4�ֽڣ�����Ϊ��data��
	//uint32_t subChunk2Size;	//4�ֽڣ������ܳ���
	};

private:
	//�ļ���
	std::ifstream fdata;

	//�ļ���
	std::string mFileName = "";
	//�ļ���С
	uint32_t mFileSize = 0;
	//��Ƶ������ʼλ��
	uint16_t mAudioDataBegin = 0;
	//��Ƶ���ݴ�С
	uint32_t mAudioDataSize = 0;
	//��Ƶ������
	int mAudioSampleRate = 0;
	//��Ƶ���ݸ�ʽ��λ��8λ��16λ��
	uint16_t mBitsPerSample = 0;
	//��Ƶ������
	uint16_t mAudioChannels = 0;

	// ������Ƶ����
	std::vector<uint8_t> mAudioData;

public:

	//���캯���������ļ�·��
	WAV_File(std::string filePath);
	//����
	~WAV_File();

	//���ļ������¼�����Ƶ�ļ���
	bool Open(std::string filePath);

	// ��ò�����
	uint32_t GetSampleRate() const { return mAudioSampleRate; }
	// ��ò���λ��8λ��16λ��
	uint8_t GetBitsPerSample() const { return mBitsPerSample; }
	// ���������
	uint8_t GetChannels() const { return mAudioChannels; }
	// ��ȡ��Ƶ��������
	std::vector<uint8_t>& GetAudioData();
};

