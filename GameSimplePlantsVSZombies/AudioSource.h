#pragma once
#include "ComponentBase.h"
#include <unordered_map>
#include "AudioDevice.h"

/// <summary>
/// 音源组件：场景小喇叭
/// </summary>
class AudioSource :
	public ComponentBase
{
private:
	// 储存音频路径和音频数据包的容器
	std::unordered_map<std::string, AudioPackage*> mPlayers;

public:

	// 析构函数
	~AudioSource();

	// 播放
	void Play(std::string path, bool needLoop = false);
	// 暂停
	//void Pause(){}
	// 停止
	void Stop(std::string path);
};

