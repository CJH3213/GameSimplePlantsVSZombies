#pragma once
#include "ComponentBase.h"
#include <vector>
#include <unordered_map>
#include "Vector2.h"
#include <functional>

/// <summary>
/// 动画组件
/// </summary>
class Animator
	: public ComponentBase
{
private:
	// 关键帧
	struct Keyframe
	{
		// 执行所在帧
		//uint16_t frameNum = 0;
		// 执行所在时间
		float time = 0.0f;
		// 变换状态
		Vector2 position = { 0.0f, 0.0f };
		float rotation = 0.0f;
		Vector2 scale = { 1.0f, 1.0f };
		// 回调函数
		std::function<void()> action = [] {};
	};

private:
	// 播放速度，暂时不知道怎么实现变速和倒放
	float mSpeed = 1.0f;

	// 现播放帧计数
	//uint16_t mFrameCount = 0;
	// 播放计时
	float mTimeBegin = 0.0f;
	// 正在播放的动作组
	std::vector<Keyframe>* mPlaying = nullptr;
	// 上一关键帧，容器索引
	size_t mKeyIndex = 0;

	// 运动关键帧
	std::unordered_map<std::string, std::vector<Keyframe>> mKeyframes;

public:

	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 添加动作组
	void AddKeyframe(std::string name, const std::vector<Keyframe>& frames);
	// 移除动作组
	void RemoveKeyframe(std::string name);

	// 播放动作组
	void Play(std::string name);
	// 停止播放
	void Stop();
	// 重新播放当前动作组
	void RePlay();

	// 组件更新
	virtual void Update() override;
};

