#include "Animator.h"
#include "GameObject.h"
#include "Time.h"

ComponentBase* Animator::Clone() const
{
	Animator* newComp = new Animator();
	// 复制速度设定
	newComp->mSpeed = mSpeed;

	// 正在播放的参数就不复制了
	// 因为容器已经不同，不能用同一个指针了

	// 拷贝运动关键帧列表
	for (auto keyframe : mKeyframes)
	{
		newComp->AddKeyframe(keyframe.first, keyframe.second);
	}

	return newComp;
}

void Animator::AddKeyframe(std::string name, const std::vector<Keyframe>& frames)
{
	mKeyframes.emplace( name, frames );
}

void Animator::RemoveKeyframe(std::string name)
{
	auto iter = mKeyframes.find(name);
	if (iter != mKeyframes.end())
	{
		if (mPlaying == &(*iter).second)
			Stop();

		(*iter).second.clear();
		mKeyframes.erase(iter);
	}
}

void Animator::Update()
{
	if (mPlaying != nullptr)		// 首先得指定了动作组
	{
		if (mKeyIndex < mPlaying->size()-1)	// 其次关键帧没播完
		{
			// 获取当前帧前后两个关键帧
			auto& kf1 = mPlaying->at(mKeyIndex);
			auto& kf2 = mPlaying->at(mKeyIndex + 1);
			// 获取已经播放时间
			float time = (Time::Time_s() - mTimeBegin) * mSpeed;
			//偶尔计时值比后关键帧时间大，会出现动作过量，以后关键帧时间为准
			float timeMin = Math::Min(time, kf2.time);		
			//SDL_Log("deltaTime:%f", delta);
			// 通过补间方式，获得当前变换状态，线性平均值
			Vector2 position = 
			{ Vector2::LinearEquation(timeMin, {kf1.time, kf1.position.x}, { kf2.time, kf2.position.x }) ,
			Vector2::LinearEquation(timeMin, {kf1.time, kf1.position.y}, { kf2.time, kf2.position.y }) };
			float rotation = Vector2::LinearEquation(timeMin, { kf1.time, kf1.rotation }, { kf2.time, kf2.rotation });
			Vector2 scale =
			{ Vector2::LinearEquation(timeMin, {kf1.time, kf1.scale.x}, { kf2.time, kf2.scale.x }) ,
			Vector2::LinearEquation(timeMin, {kf1.time, kf1.scale.y}, { kf2.time, kf2.scale.y }) };;
			// 控制游戏对象的变换组件
			mGameObject->mTransform->SetPosition(position);
			mGameObject->mTransform->SetRotation(rotation);
			mGameObject->mTransform->SetScale(scale);
			//帧、索引累加
			//mFrameCount++;
			if (time >= kf2.time)
			{
				mKeyIndex++;
				// 执行关键帧回调函数
				mPlaying->at(mKeyIndex).action();
			}
		}
	}
}

void Animator::Play(std::string name)
{
	auto iter = mKeyframes.find(name);
	if (iter != mKeyframes.end())
	{
		// 初始化播放参数
		//mFrameCount = 0;
		mPlaying = &((*iter).second);
		RePlay();
		// 执行关键帧回调函数
		mPlaying->at(mKeyIndex).action();
	}
}

void Animator::RePlay()
{
	//mFrameCount = 0;
	mTimeBegin = Time::Time_s();
	mKeyIndex = 0;
}

void Animator::Stop()
{
	//mFrameCount = 0;
	mPlaying = nullptr;
	RePlay();
}
