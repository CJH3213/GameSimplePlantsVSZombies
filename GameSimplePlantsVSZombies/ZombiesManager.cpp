#include "ZombiesManager.h"
#include "SceneBase.h"
#include "Zombie.h"
#include "Time.h"
#include "Random.h"
#include <fstream>
#include "JsonObject.h"
#include "FlagMeterScript.h"
#include "FlagMeter.h"
#include "LifeScript.h"
#include "Texture.h"
#include "Game.h"
#include "AudioSource.h"
#include "TextureRender.h"
#include "Animator.h"
#include "ZombieScript.h"

void ZombiesManager::LoadLevelZombiesData()
{
	// 记录每波僵尸个数
	std::vector<int> wavesZombiesNum;

	// 加载关卡数据Json文件
	std::ifstream file("Resource/Level_1_1.json", std::ios::in | std::ios::binary);
	std::string jsonData((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));
	file.close();

	// 以下解析Json内容
	JsonValue root(jsonData);
	auto rootMap = root.GetObjs();

	// 获取本场关卡出场僵尸列表（感觉这个不是很必要，可以在读取任务中统计）
	auto zombiesArr = rootMap["Zombies"].GetArray();
	auto zombiesArr_0 = zombiesArr[0].GetString();
	// 获取奖品名称
	mPrize = rootMap["Prize"].GetString();

	// 获取本场进度任务列表
	auto tasksArr = rootMap["Tasks"].GetArray();
	for (auto taskValue : tasksArr)
	{
		auto task = taskValue.GetObjs();
		auto taskType = task["Type"].GetString();

		BaseTask* baseTaskObj = nullptr;

		// 根据不同标识封装成不同的任务类型
		// 延时器任务
		if (taskType == "Delay")
		{
			DelayTask* taskObj = new DelayTask;
			baseTaskObj = (BaseTask*)taskObj;
			taskObj->mTime = task["Time"].GetDouble();
		}

		// 生成波次僵尸任务
		else if (taskType == "Wave")
		{
			WaveTask* taskObj = new WaveTask;
			baseTaskObj = (BaseTask*)taskObj;
			// 随机僵尸生成参数
			auto taskRandom = task["Random Zombies"].GetObjs();
			taskObj->mInterval = taskRandom["Interval"].GetDouble();
			taskObj->mNumber = taskRandom["Number"].GetInt();
			auto taskRandomZombies = taskRandom["Zombies"].GetArray();
			for (auto zomb : taskRandomZombies)
				taskObj->mRandomZombies.emplace_back(
					zomb.GetString());
			// 特定僵尸生成参数
			auto taskSpecific = task["Specific Zombies"].GetArray();
			for (auto zomb : taskSpecific)
			{
				auto zombObj = zomb.GetObjs();
				taskObj->mSpecificZombies.emplace_back(
					zombObj["Zombie"].GetString(), zombObj["Time"].GetDouble());
			}

			// 累计本波次僵尸生成数量=随机+特定
			int waveZombies = taskObj->mNumber + taskObj->mSpecificZombies.size();
			mTotalZombies += waveZombies;
			wavesZombiesNum.emplace_back(waveZombies);
		}

		if(baseTaskObj != nullptr)
		{
			baseTaskObj->mZombiesManager = this;
			mTasks.emplace_back(baseTaskObj);
		}
	}

	// 根据进度添加旗子
	int sumZombies = 0;
	for (auto num : wavesZombiesNum)
	{
		sumZombies += num;
		mFlagMeter->AddFlag((float)sumZombies / mTotalZombies);
	}
}

void ZombiesManager::Awards()
{
	// 切换音乐
	auto audio = GetScene()->FindGameObject("AdventureAudio")->GetComponent<AudioSource>();
	audio->Stop("Resource/Sounds/Grasswalk.wav");
	audio->Play("Resource/Sounds/winmusic.wav");

	// 显示颁奖动图
	GameObject* prizeObj = new GameObject("");
	GetScene()->AddGameObject(prizeObj);
	Vector2 winCenter = GetGame()->mWindow->GetSize() / 2;
	prizeObj->mTransform->SetPosition(winCenter);
	// 渲染组件
	Texture* prizeTexture = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/trophy_hi_res.png");
	TextureRender* prizeRender = new TextureRender(prizeTexture, 0);
	prizeObj->AddComponent(prizeRender);
	// 动作组件
	Animator* prizeAnim = new Animator();
	prizeObj->AddComponent(prizeAnim);
	prizeAnim->AddKeyframe("GrowLarger", {
		{0.0f, winCenter, 0.0f, {0.1f, 0.1f}},
		{1.5f, winCenter, 0.0f, {1.5f, 1.5f}}
		});
	prizeAnim->Play("GrowLarger");
}

void ZombiesManager::Lose()
{
	// 切换音乐
	auto audio = GetScene()->FindGameObject("AdventureAudio")->GetComponent<AudioSource>();
	audio->Stop("Resource/Sounds/Grasswalk.wav");
	audio->Play("Resource/Sounds/losemusic.wav");
	audio->Play("Resource/Sounds/scream.wav");

	// 显示颁奖动图
	GameObject* prizeObj = new GameObject("");
	GetScene()->AddGameObject(prizeObj);
	Vector2 winCenter = GetGame()->mWindow->GetSize() / 2;
	prizeObj->mTransform->SetPosition(winCenter);
	// 渲染组件
	Texture* prizeTexture = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/ZombiesWon.png");
	TextureRender* prizeRender = new TextureRender(prizeTexture, 0);
	prizeObj->AddComponent(prizeRender);
	// 动作组件
	Animator* prizeAnim = new Animator();
	prizeObj->AddComponent(prizeAnim);
	prizeAnim->AddKeyframe("GrowLarger", {
		{0.0f, winCenter, 0.0f, {0.2f, 0.2f}},
		{2.0f, winCenter, 0.0f, {1.0f, 1.0f}}
		});
	prizeAnim->Play("GrowLarger");
}

void ZombiesManager::Start()
{
	// 获取背景图片对象引用
	mBackGround = GetScene()->FindGameObject("BackGround");
	// 获取关卡进度条脚本引用
	GameObject* flagMeterObj = GetScene()->FindGameObject("FlagMeter");
	mFlagMeter = flagMeterObj->GetComponent< FlagMeterScript>();
	flagMeterObj->SetActive(true);

	// 加载关卡僵尸数据
	LoadLevelZombiesData();
	// 初始关卡任务
	mTasks[mTasksIndex = 0]->Start();
}

void ZombiesManager::Update()
{
	if(mGameOver == false)
	{
		// 执行关卡任务
		if (mTasksIndex < mTasks.size())
		{
			// 当前任务的更新
			bool isFinished = (mTasks[mTasksIndex])->Updata();

			// 若当前任务执行完毕，预备下一个任务
			if (isFinished == true)
			{
				if (++mTasksIndex < mTasks.size())
					mTasks[mTasksIndex]->Start();
			}
		}

		// 任务全部完成且僵尸全部死亡，颁奖
		else if (mAliveZombiesNum <= 0)
		{
			mGameOver = true;
			Awards();
		}
	}
}

void ZombiesManager::CreateZombie(std::string type, int x, int y)
{
	// 实例僵尸对象
	Zombie* newZombie = new Zombie();
	GetScene()->AddGameObject(newZombie);
	newZombie->SetParent(mBackGround);

	// 依赖注入僵尸管理器到僵尸对象
	ZombieScript* zomScript = newZombie->GetComponent<ZombieScript>();
	zomScript->mZomManager = this;

	mAliveZombiesNum++;
	mAliveZombies.emplace(zomScript);

	// 监听僵尸死亡事件
	LifeScript* lifeScr = newZombie->GetComponent<LifeScript>();
	lifeScr->mChangeEvents.AddListener("ZombiesManager", [this, zomScript](float hp) 
		{
			if(hp <= 0.0f)
			{
				mAliveZombiesNum--;
				mAliveZombies.erase(zomScript);
			}
		});

	// 指定生成行
	y = Math::Clamp(y, 0, 4);
	Vector2 pos = { 810, mBeginYPos[y] };
	newZombie->mTransform->SetPosition(pos);

	// 计算关卡进度
	mCountZombies++;
	mFlagMeter->SetProgress((float)mCountZombies / mTotalZombies);
}

void ZombiesManager::ZombiesWon()
{
	mGameOver = true;

	for (auto zombie : mAliveZombies)
	{
		zombie->StopMove();
	}

	mGameOver = true;
	Lose();
}
