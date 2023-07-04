#pragma once
#include <SDL_audio.h>
#include <vector>
#include <mutex>

class AudioPackage;

/// <summary>
/// 音频设备单例
/// 由于SDL只能同时启用一个音频设备，所以使用单例模式管理
/// </summary>
class AudioDevice
{
private:
    // 构造
    AudioDevice();
    // 析构
    ~AudioDevice() = default;
    // 禁止复制和赋值
    AudioDevice(const AudioDevice&) = delete;
    AudioDevice& operator=(const AudioDevice&) = delete;

private:
    // 是否已打开音频设备
    bool mIsOpened = false;
    // 初始化SDL音频设备
    SDL_AudioSpec mDesiredSpec;
    // 音频数据包容器
    std::vector<class AudioPackage*> mAudioPackages;
    // 访问容器互斥锁
    std::mutex mMutex;

    // SDL音频流回调
    static void AudioCallback(void* userdata, uint8_t* stream, int len);

public:
    // 获取音频设备单例
    static AudioDevice& GetInstance()
    {
        static AudioDevice instance;  // 通过静态局部变量确保只创建一次实例
        return instance;
    }

    // 启用音频设备
    static void Open();
    // 关闭音频设备
    static void Close();
    // 播放音频
    static void Play(AudioPackage* pack);
    // 移除音频
    static void Remove(AudioPackage* pack);

    // 加载WAV音频文件
    static AudioPackage* LoadWav(std::string path);
};

class AudioPackage
{
public:
    // SDL音频信息
    SDL_AudioSpec mDesiredSpec;
    // 是否循环播放
    bool mIsLoop = false;
    // 音量
    float mVolume = 1.0f;
    // 当前播放进度
    size_t mPlaybackProgress = 0;
    // 音频数据
    std::vector<uint8_t> mData;
};

