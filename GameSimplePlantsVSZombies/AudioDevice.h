#pragma once
#include <SDL_audio.h>
#include <vector>
#include <mutex>

class AudioPackage;

/// <summary>
/// ��Ƶ�豸����
/// ����SDLֻ��ͬʱ����һ����Ƶ�豸������ʹ�õ���ģʽ����
/// </summary>
class AudioDevice
{
private:
    // ����
    AudioDevice();
    // ����
    ~AudioDevice() = default;
    // ��ֹ���ƺ͸�ֵ
    AudioDevice(const AudioDevice&) = delete;
    AudioDevice& operator=(const AudioDevice&) = delete;

private:
    // �Ƿ��Ѵ���Ƶ�豸
    bool mIsOpened = false;
    // ��ʼ��SDL��Ƶ�豸
    SDL_AudioSpec mDesiredSpec;
    // ��Ƶ���ݰ�����
    std::vector<class AudioPackage*> mAudioPackages;
    // ��������������
    std::mutex mMutex;

    // SDL��Ƶ���ص�
    static void AudioCallback(void* userdata, uint8_t* stream, int len);

public:
    // ��ȡ��Ƶ�豸����
    static AudioDevice& GetInstance()
    {
        static AudioDevice instance;  // ͨ����̬�ֲ�����ȷ��ֻ����һ��ʵ��
        return instance;
    }

    // ������Ƶ�豸
    static void Open();
    // �ر���Ƶ�豸
    static void Close();
    // ������Ƶ
    static void Play(AudioPackage* pack);
    // �Ƴ���Ƶ
    static void Remove(AudioPackage* pack);

    // ����WAV��Ƶ�ļ�
    static AudioPackage* LoadWav(std::string path);
};

class AudioPackage
{
public:
    // SDL��Ƶ��Ϣ
    SDL_AudioSpec mDesiredSpec;
    // �Ƿ�ѭ������
    bool mIsLoop = false;
    // ����
    float mVolume = 1.0f;
    // ��ǰ���Ž���
    size_t mPlaybackProgress = 0;
    // ��Ƶ����
    std::vector<uint8_t> mData;
};

