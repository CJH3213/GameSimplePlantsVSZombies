#pragma once
#include "ComponentBase.h"
#include <array>
#include "Vector2.h"
#include <vector>
#include <memory>
#include "TaskClass.h"
#include <set>

class ZombiesManager :
	public ComponentBase
{
private:
	// ��ʬ��
	int mAliveZombiesNum = 0;
	// ��ʬ
	std::set<class ZombieScript*> mAliveZombies;
	// �ؿ��Ƿ����
	bool mGameOver = false;

	// ÿ������λ��y
	std::array<float, 5> mBeginYPos = {125, 225, 325, 425, 525};
	// ÿ������λ��x
	//std::array<float, 9> mBeginXPos = { 125, 225, 325, 425, 525 };
	// ÿ���ݸ��С
	Vector2 mTurfSize;
	// ���ϲݸ���������
	Vector2 mTurf0Center;
	// �ݸ��������
	Vector2 mTurfNum;

	// ������������
	GameObject* mBackGround = nullptr;
	// �ؿ��������ű�����
	class FlagMeterScript* mFlagMeter = nullptr;

	// ������ʬ�б�
	std::vector<std::string> mZombies;
	// ͨ�ؽ�Ʒ
	std::string mPrize;
	// ���������б�
	std::vector<std::unique_ptr<BaseTask>> mTasks;
	// ������ȣ��±꣩
	size_t mTasksIndex = 0;
	// �ܽ�ʬ����
	uint32_t mTotalZombies = 0;
	// ��������ʬ����
	uint32_t mCountZombies = 0;

	// ���عؿ���ʬ����
	void LoadLevelZombiesData();
	// ͨ�ذ佱
	void Awards();
	// ͨ��ʧ��
	void Lose();

public:

	// �ű���ʼ��
	virtual void Start() override;
	// �߼�����
	virtual void Update() override;

	// ���ɽ�ʬl
	void CreateZombie(std::string type, int x, int y);
	// ��ʬʤ��
	void ZombiesWon();
};

