#pragma once
#include <vector>
#include <string>

class BaseTask
{
public:
	class ZombiesManager* mZombiesManager = nullptr;

	virtual void Start() = 0;
	virtual bool Updata() = 0;
};

class DelayTask : public BaseTask
{
private:
	float mNextTime;
public:
	float mTime;

	virtual void Start() override;
	virtual bool Updata() override;
};

class WaveTask : public BaseTask
{
private:
	float mBeginTime;
	float mNextTime;
	size_t mRandomIndex = 0;
	size_t mSpecificIndex = 0;
public:
	float mInterval;
	int mNumber;
	std::vector<std::string> mRandomZombies;
	std::vector<std::pair<std::string, float>> mSpecificZombies;

	virtual void Start() override;
	virtual bool Updata() override;
};

