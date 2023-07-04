#include "Animator.h"
#include "GameObject.h"
#include "Time.h"

ComponentBase* Animator::Clone() const
{
	Animator* newComp = new Animator();
	// �����ٶ��趨
	newComp->mSpeed = mSpeed;

	// ���ڲ��ŵĲ����Ͳ�������
	// ��Ϊ�����Ѿ���ͬ��������ͬһ��ָ����

	// �����˶��ؼ�֡�б�
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
	if (mPlaying != nullptr)		// ���ȵ�ָ���˶�����
	{
		if (mKeyIndex < mPlaying->size()-1)	// ��ιؼ�֡û����
		{
			// ��ȡ��ǰ֡ǰ�������ؼ�֡
			auto& kf1 = mPlaying->at(mKeyIndex);
			auto& kf2 = mPlaying->at(mKeyIndex + 1);
			// ��ȡ�Ѿ�����ʱ��
			float time = (Time::Time_s() - mTimeBegin) * mSpeed;
			//ż����ʱֵ�Ⱥ�ؼ�֡ʱ��󣬻���ֶ����������Ժ�ؼ�֡ʱ��Ϊ׼
			float timeMin = Math::Min(time, kf2.time);		
			//SDL_Log("deltaTime:%f", delta);
			// ͨ�����䷽ʽ����õ�ǰ�任״̬������ƽ��ֵ
			Vector2 position = 
			{ Vector2::LinearEquation(timeMin, {kf1.time, kf1.position.x}, { kf2.time, kf2.position.x }) ,
			Vector2::LinearEquation(timeMin, {kf1.time, kf1.position.y}, { kf2.time, kf2.position.y }) };
			float rotation = Vector2::LinearEquation(timeMin, { kf1.time, kf1.rotation }, { kf2.time, kf2.rotation });
			Vector2 scale =
			{ Vector2::LinearEquation(timeMin, {kf1.time, kf1.scale.x}, { kf2.time, kf2.scale.x }) ,
			Vector2::LinearEquation(timeMin, {kf1.time, kf1.scale.y}, { kf2.time, kf2.scale.y }) };;
			// ������Ϸ����ı任���
			mGameObject->mTransform->SetPosition(position);
			mGameObject->mTransform->SetRotation(rotation);
			mGameObject->mTransform->SetScale(scale);
			//֡�������ۼ�
			//mFrameCount++;
			if (time >= kf2.time)
			{
				mKeyIndex++;
				// ִ�йؼ�֡�ص�����
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
		// ��ʼ�����Ų���
		//mFrameCount = 0;
		mPlaying = &((*iter).second);
		RePlay();
		// ִ�йؼ�֡�ص�����
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
