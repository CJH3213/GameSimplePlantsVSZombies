#include "TaskClass.h"
#include "Time.h"
#include "Random.h"
#include "ZombiesManager.h"
#include "SceneBase.h"
#include "AudioSource.h"
#include "Texture.h"
#include "Game.h"
#include "TextureRender.h"

void DelayTask::Start()
{
    mNextTime = Time::Time_s() + mTime;
}

bool DelayTask::Updata()
{
    return (mNextTime < Time::Time_s());
}

void WaveTask::Start()
{
    mBeginTime = Time::Time_s();    //����ʼ�¼�
    mNextTime = Time::Time_s() + mInterval;
}

bool WaveTask::Updata()
{
    // �����ʬ����
    float time = Time::Time_s();
    if (mNextTime < time && mNumber > 0)
    {
        mNextTime += mInterval;
        mNumber--;

        // ���б����������ʬ����
        size_t index = Random((size_t)0, mRandomZombies.size()-1);
        std::string name = mRandomZombies[index];
        // �����
        int row = Random(0, 4);
        // ���ý�ʬ�����������ɷ���
        mZombiesManager->CreateZombie(name, -1, row);
    }

    // ָ����ʬ����
    float taskTime = time - mBeginTime;
    if (mSpecificIndex < mSpecificZombies.size() &&
        mSpecificZombies[mSpecificIndex].second <= taskTime)
    {
        // ���ý�ʬ�����������ɷ���
        std::string name = mSpecificZombies[mSpecificIndex].first;
        int row = Random(0, 4);
        mZombiesManager->CreateZombie(name, -1, row);
        // �ݽ��´�����
        mSpecificIndex++;
    }

    return (mNumber<=0 && mSpecificIndex >= mSpecificZombies.size());
}
