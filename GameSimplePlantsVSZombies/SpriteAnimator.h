#pragma once
#include "ComponentBase.h"
#include "IRenderer.h"
#include "Texture.h"
#include <functional>
#include <unordered_map>
#include <vector>

class SpriteAnimator : 
	public ComponentBase, public IRenderer
{
private:
	// 关键帧
	struct Keyframe
	{
		// 执行所在时间
		Texture* texture = nullptr;
		// 回调函数
		std::function<void()> action = [] {};
	};
	// 动作包
	struct KeyAction
	{
		int frameIndex = 0;
		std::function<void()> action = [] {};
	};

private:
	// 速度
	int mAnimFPS = 10;
	// 播放计时
	//float mTimeBegin = 0.0f;
	// 上一帧时间
	float mTimeLast = 0.0f;
	// 当前帧（使用浮点数减少累计偏差）
	float mCurrFrame = 0;
	// 当前纹理组
	std::vector<Keyframe>* mPlaying = nullptr;

	// 帧动画组容器
	std::unordered_map<std::string, std::vector<Keyframe>>	 mTextures;

public:

	// 渲染层级（深度）
	int mDrawOrder = 100;

	// 析构
	~SpriteAnimator();
	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 添加帧动画组
	void AddTextures(std::string name, const std::vector<Texture*>& textures);
	// 移除帧动画组
	void RemoveTextures(std::string name);
	// 添加回调事件
	void AddActions(std::string name, const std::vector<KeyAction>& actions);

	// 设置播放帧率
	void SetFPS(int fps) { mAnimFPS = fps; }
	// 播放动作组
	void Play(std::string name);
	// 重新播放当前动作组
	void RePlay();
	// 停止播放
	void Stop();

	// 组件初始
	virtual void Awake() override;
	// 组件更新
	virtual void Update() override;

	/******************渲染接口实现******************/
	// 是否启用渲染
	virtual bool IsRenderEnable() override { return IsEnable(); }
	// 获取绘制层级
	virtual int GetDrawOrder() const  override { return mDrawOrder; }
	// 绘制接口
	virtual void OnRender(Window* w) override;
};

