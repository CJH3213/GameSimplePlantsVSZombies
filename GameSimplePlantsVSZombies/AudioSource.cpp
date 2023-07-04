#include "AudioSource.h"

#include <SDL_log.h>
#include <algorithm>


AudioSource::~AudioSource()
{
	for (auto& player : mPlayers)
	{
		AudioDevice::Remove(player.second);
		delete player.second;
	}
	mPlayers.clear();
}

void AudioSource::Play(std::string path, bool needLoop)
{
	auto it = mPlayers.find(path);
	if (it == mPlayers.end())
	{
		// 获取路径后4个字符作为文件后缀
		std::string ext = path.substr(path.size() - 4, path.size() - 1);
		// 将字符串转换为小写
		std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) {
			return std::tolower(c);
			});
		if (ext != ".wav")
		{
			SDL_Log(u8"不支持Wav格式以外的音频");
			return;
		}

		AudioPackage* pack = AudioDevice::LoadWav(path);
		pack->mIsLoop = needLoop;
		if (pack != nullptr)
		{
			mPlayers.emplace(path, pack);
			AudioDevice::Play(pack);
		}
	}
	else
		AudioDevice::Play((*it).second);
}

void AudioSource::Stop(std::string path)
{
	auto it = mPlayers.find(path);
	if (it != mPlayers.end())
	{
		AudioDevice::Remove((*it).second);
	}
}

