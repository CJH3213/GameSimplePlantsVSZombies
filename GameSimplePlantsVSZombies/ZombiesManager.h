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
	// 存活僵尸数
	int mAliveZombiesNum = 0;
	// 存活僵尸
	std::set<class ZombieScript*> mAliveZombies;
	// 关卡是否结束
	bool mGameOver = false;

	// 每行生成位置y
	std::array<float, 5> mBeginYPos = {125, 225, 325, 425, 525};
	// 每行生成位置x
	//std::array<float, 9> mBeginXPos = { 125, 225, 325, 425, 525 };
	// 每个草格大小
	Vector2 mTurfSize;
	// 左上草格中心坐标
	Vector2 mTurf0Center;
	// 草格横竖个数
	Vector2 mTurfNum;

	// 背景对象引用
	GameObject* mBackGround = nullptr;
	// 关卡进度条脚本引用
	class FlagMeterScript* mFlagMeter = nullptr;

	// 本场僵尸列表
	std::vector<std::string> mZombies;
	// 通关奖品
	std::string mPrize;
	// 本场任务列表
	std::vector<std::unique_ptr<BaseTask>> mTasks;
	// 任务进度（下标）
	size_t mTasksIndex = 0;
	// 总僵尸数量
	uint32_t mTotalZombies = 0;
	// 已死亡僵尸数量
	uint32_t mCountZombies = 0;

	// 加载关卡僵尸数据
	void LoadLevelZombiesData();
	// 通关颁奖
	void Awards();
	// 通关失败
	void Lose();

public:

	// 脚本初始化
	virtual void Start() override;
	// 逻辑更新
	virtual void Update() override;

	// 生成僵尸l
	void CreateZombie(std::string type, int x, int y);
	// 僵尸胜利
	void ZombiesWon();
};

