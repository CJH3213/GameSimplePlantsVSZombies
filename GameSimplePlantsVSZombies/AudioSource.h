#pragma once
#include "ComponentBase.h"
#include <unordered_map>
#include "AudioDevice.h"

/// <summary>
/// ��Դ���������С����
/// </summary>
class AudioSource :
	public ComponentBase
{
private:
	// ������Ƶ·������Ƶ���ݰ�������
	std::unordered_map<std::string, AudioPackage*> mPlayers;

public:

	// ��������
	~AudioSource();

	// ����
	void Play(std::string path, bool needLoop = false);
	// ��ͣ
	//void Pause(){}
	// ֹͣ
	void Stop(std::string path);
};

