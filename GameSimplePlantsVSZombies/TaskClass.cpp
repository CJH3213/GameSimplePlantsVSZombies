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
    mBeginTime = Time::Time_s();    //任务开始事件
    mNextTime = Time::Time_s() + mInterval;
}

bool WaveTask::Updata()
{
    // 随机僵尸产生
    float time = Time::Time_s();
    if (mNextTime < time && mNumber > 0)
    {
        mNextTime += mInterval;
        mNumber--;

        // 从列表随机产生僵尸种类
        size_t index = Random((size_t)0, mRandomZombies.size()-1);
        std::string name = mRandomZombies[index];
        // 随机行
        int row = Random(0, 4);
        // 调用僵尸管理器的生成方法
        mZombiesManager->CreateZombie(name, -1, row);
    }

    // 指定僵尸产生
    float taskTime = time - mBeginTime;
    if (mSpecificIndex < mSpecificZombies.size() &&
        mSpecificZombies[mSpecificIndex].second <= taskTime)
    {
        // 调用僵尸管理器的生成方法
        std::string name = mSpecificZombies[mSpecificIndex].first;
        int row = Random(0, 4);
        mZombiesManager->CreateZombie(name, -1, row);
        // 递进下次任务
        mSpecificIndex++;
    }

    return (mNumber<=0 && mSpecificIndex >= mSpecificZombies.size());
}
