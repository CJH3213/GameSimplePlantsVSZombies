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
	// ��¼ÿ����ʬ����
	std::vector<int> wavesZombiesNum;

	// ���عؿ�����Json�ļ�
	std::ifstream file("Resource/Level_1_1.json", std::ios::in | std::ios::binary);
	std::string jsonData((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));
	file.close();

	// ���½���Json����
	JsonValue root(jsonData);
	auto rootMap = root.GetObjs();

	// ��ȡ�����ؿ�������ʬ�б��о�������Ǻܱ�Ҫ�������ڶ�ȡ������ͳ�ƣ�
	auto zombiesArr = rootMap["Zombies"].GetArray();
	auto zombiesArr_0 = zombiesArr[0].GetString();
	// ��ȡ��Ʒ����
	mPrize = rootMap["Prize"].GetString();

	// ��ȡ�������������б�
	auto tasksArr = rootMap["Tasks"].GetArray();
	for (auto taskValue : tasksArr)
	{
		auto task = taskValue.GetObjs();
		auto taskType = task["Type"].GetString();

		BaseTask* baseTaskObj = nullptr;

		// ���ݲ�ͬ��ʶ��װ�ɲ�ͬ����������
		// ��ʱ������
		if (taskType == "Delay")
		{
			DelayTask* taskObj = new DelayTask;
			baseTaskObj = (BaseTask*)taskObj;
			taskObj->mTime = task["Time"].GetDouble();
		}

		// ���ɲ��ν�ʬ����
		else if (taskType == "Wave")
		{
			WaveTask* taskObj = new WaveTask;
			baseTaskObj = (BaseTask*)taskObj;
			// �����ʬ���ɲ���
			auto taskRandom = task["Random Zombies"].GetObjs();
			taskObj->mInterval = taskRandom["Interval"].GetDouble();
			taskObj->mNumber = taskRandom["Number"].GetInt();
			auto taskRandomZombies = taskRandom["Zombies"].GetArray();
			for (auto zomb : taskRandomZombies)
				taskObj->mRandomZombies.emplace_back(
					zomb.GetString());
			// �ض���ʬ���ɲ���
			auto taskSpecific = task["Specific Zombies"].GetArray();
			for (auto zomb : taskSpecific)
			{
				auto zombObj = zomb.GetObjs();
				taskObj->mSpecificZombies.emplace_back(
					zombObj["Zombie"].GetString(), zombObj["Time"].GetDouble());
			}

			// �ۼƱ����ν�ʬ��������=���+�ض�
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

	// ���ݽ����������
	int sumZombies = 0;
	for (auto num : wavesZombiesNum)
	{
		sumZombies += num;
		mFlagMeter->AddFlag((float)sumZombies / mTotalZombies);
	}
}

void ZombiesManager::Awards()
{
	// �л�����
	auto audio = GetScene()->FindGameObject("AdventureAudio")->GetComponent<AudioSource>();
	audio->Stop("Resource/Sounds/Grasswalk.wav");
	audio->Play("Resource/Sounds/winmusic.wav");

	// ��ʾ�佱��ͼ
	GameObject* prizeObj = new GameObject("");
	GetScene()->AddGameObject(prizeObj);
	Vector2 winCenter = GetGame()->mWindow->GetSize() / 2;
	prizeObj->mTransform->SetPosition(winCenter);
	// ��Ⱦ���
	Texture* prizeTexture = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/trophy_hi_res.png");
	TextureRender* prizeRender = new TextureRender(prizeTexture, 0);
	prizeObj->AddComponent(prizeRender);
	// �������
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
	// �л�����
	auto audio = GetScene()->FindGameObject("AdventureAudio")->GetComponent<AudioSource>();
	audio->Stop("Resource/Sounds/Grasswalk.wav");
	audio->Play("Resource/Sounds/losemusic.wav");
	audio->Play("Resource/Sounds/scream.wav");

	// ��ʾ�佱��ͼ
	GameObject* prizeObj = new GameObject("");
	GetScene()->AddGameObject(prizeObj);
	Vector2 winCenter = GetGame()->mWindow->GetSize() / 2;
	prizeObj->mTransform->SetPosition(winCenter);
	// ��Ⱦ���
	Texture* prizeTexture = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/ZombiesWon.png");
	TextureRender* prizeRender = new TextureRender(prizeTexture, 0);
	prizeObj->AddComponent(prizeRender);
	// �������
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
	// ��ȡ����ͼƬ��������
	mBackGround = GetScene()->FindGameObject("BackGround");
	// ��ȡ�ؿ��������ű�����
	GameObject* flagMeterObj = GetScene()->FindGameObject("FlagMeter");
	mFlagMeter = flagMeterObj->GetComponent< FlagMeterScript>();
	flagMeterObj->SetActive(true);

	// ���عؿ���ʬ����
	LoadLevelZombiesData();
	// ��ʼ�ؿ�����
	mTasks[mTasksIndex = 0]->Start();
}

void ZombiesManager::Update()
{
	if(mGameOver == false)
	{
		// ִ�йؿ�����
		if (mTasksIndex < mTasks.size())
		{
			// ��ǰ����ĸ���
			bool isFinished = (mTasks[mTasksIndex])->Updata();

			// ����ǰ����ִ����ϣ�Ԥ����һ������
			if (isFinished == true)
			{
				if (++mTasksIndex < mTasks.size())
					mTasks[mTasksIndex]->Start();
			}
		}

		// ����ȫ������ҽ�ʬȫ���������佱
		else if (mAliveZombiesNum <= 0)
		{
			mGameOver = true;
			Awards();
		}
	}
}

void ZombiesManager::CreateZombie(std::string type, int x, int y)
{
	// ʵ����ʬ����
	Zombie* newZombie = new Zombie();
	GetScene()->AddGameObject(newZombie);
	newZombie->SetParent(mBackGround);

	// ����ע�뽩ʬ����������ʬ����
	ZombieScript* zomScript = newZombie->GetComponent<ZombieScript>();
	zomScript->mZomManager = this;

	mAliveZombiesNum++;
	mAliveZombies.emplace(zomScript);

	// ������ʬ�����¼�
	LifeScript* lifeScr = newZombie->GetComponent<LifeScript>();
	lifeScr->mChangeEvents.AddListener("ZombiesManager", [this, zomScript](float hp) 
		{
			if(hp <= 0.0f)
			{
				mAliveZombiesNum--;
				mAliveZombies.erase(zomScript);
			}
		});

	// ָ��������
	y = Math::Clamp(y, 0, 4);
	Vector2 pos = { 810, mBeginYPos[y] };
	newZombie->mTransform->SetPosition(pos);

	// ����ؿ�����
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
