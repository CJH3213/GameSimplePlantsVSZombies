#include "ZombiesManager.h"
#include "SceneBase.h"
#include "Zombie.h"
#include "Time.h"
#include "Random.h"

void ZombiesManager::OnEnable()
{
	//GetScene()->AddGameObject(new Zombie());
}

void ZombiesManager::Start()
{
	// ��ȡ����ͼƬ��������
	mBackGround = GetScene()->FindGameObject("BackGround");

	// �������ɽ�ʬ��ʱ��
	mNextTime = Time::Time_s() + mInterval;
}

void ZombiesManager::Update()
{
	// ��ʱ���ɽ�ʬ
	if (mNextTime < Time::Time_s())
	{
		mNextTime += mInterval;

		Zombie* newZombie = new Zombie();
		GetScene()->AddGameObject(newZombie);
		newZombie->SetParent(mBackGround);

		size_t row = Random<size_t>(0, mBeginPos.size()-1);
		Vector2 pos = { 810, mBeginPos[row] };
		newZombie->mTransform->SetPosition(pos);
	}
}
