#include "SpriteAnimator.h"
#include "Game.h"
#include "Time.h"

SpriteAnimator::~SpriteAnimator()
{
	// ����ǰ�������Ⱦ�������
	GetGame()->mRenderManager->RemoveComponent(this);
	// ������������
	for (auto& map : mTextures)
	{
		for (auto& key : map.second)
			delete key.texture;
		map.second.clear();
	}
	mTextures.clear();
}

ComponentBase* SpriteAnimator::Clone() const
{
	SpriteAnimator* newComp = new SpriteAnimator();
	
	std::vector<Texture*> textures;
	for (auto& map : mTextures)
	{
		// ��һ�鶯���е���������ȡ����
		textures.clear();
		for (auto& key : map.second)
			textures.emplace_back(key.texture);

		// ����������
		newComp->AddTextures(map.first,
			const_cast<SpriteAnimator*>(this)->GetGame()->
			mImageManagement->CopyTextures(textures));

		// Ѱ�Ҳ��Ŷ���������
		if (mPlaying == &(map.second))
			newComp->Play(map.first);
	}

	return newComp;
}

void SpriteAnimator::AddTextures(std::string name, const std::vector<Texture*>& textures)
{
	std::vector<Keyframe> keys;

	for (auto tex : textures)
	{
		keys.emplace_back(std::move( Keyframe{ tex }));
	}

	mTextures.emplace(name, keys);
}

void SpriteAnimator::RemoveTextures(std::string name)
{
	auto iter = mTextures.find(name);
	if (iter != mTextures.end())
	{
		if (mPlaying == &(*iter).second)
			Stop();

		for (auto& tex : (*iter).second)
			delete tex.texture;
		(*iter).second.clear();
		mTextures.erase(iter);
	}
}

void SpriteAnimator::AddActions(std::string name, const std::vector<KeyAction>& actions)
{
	auto it = mTextures.find(name);
	if (it != mTextures.end())
	{
		for (auto& key : actions)
		{
			if (key.frameIndex < (*it).second.size())
			{
				(*it).second[key.frameIndex].action = key.action;
			}
		}
	}
}

void SpriteAnimator::Play(std::string name)
{
	auto iter = mTextures.find(name);
	if (iter != mTextures.end())
	{
		// �����ǰ���ŵĺ��趨��ͬ���򲻱���ͷ����
		if(mPlaying != &((*iter).second))
		{
			mPlaying = &((*iter).second);
			RePlay();
		}
	}
}

void SpriteAnimator::RePlay()
{
	mCurrFrame = 0.0f;
	mTimeLast = Time::Time_s();
	(*mPlaying)[mCurrFrame].action();
}

void SpriteAnimator::Stop()
{
	mPlaying = nullptr;
	//RePlay();
}

void SpriteAnimator::Awake()
{
	//����Ⱦ�����ӵ���Ⱦ������
	GetGame()->mRenderManager->AddComponent(this);
}

void SpriteAnimator::Update()
{
	if (mPlaying != nullptr)
	{
		// ��ȡ�Ѿ�����ʱ��
		float deltaTime = Time::Time_s() - mTimeLast;
		mTimeLast = Time::Time_s();
		// ������ڲ��ŵ��ڼ�֡
		float nextFrame = mCurrFrame;
		mCurrFrame += mAnimFPS * deltaTime;

		// ����Ƿ��Ѿ�����һ֡
		bool change = false;
		if ((int)mCurrFrame != (int)nextFrame)
			change = true;

		// ���࣬ʹ��ǰ֡����������֮��
		while (mCurrFrame >= mPlaying->size())
			mCurrFrame -= mPlaying->size();

		if (change = true)
			(*mPlaying)[mCurrFrame].action();
	}
}

void SpriteAnimator::OnRender(Window* w)
{
	if (mPlaying != nullptr)
	{
		// ��ȡ��ǰ����
		Texture* currTexture = (*mPlaying)[mCurrFrame].texture;

		//��ȡ��Ϸ����ռ���Ϣ
		auto transform = GetTransform();
		Vector2 scale = transform->GetScale();

		// ��ȡ�������Ͻ�����
		Vector2 leftTopPos = transform->GetPosition() -
			currTexture->GetSize() * scale / 2;

		// �������Ƶ���Ⱦ����
		w->CopyTextureToRenderer(currTexture,
			leftTopPos,
			transform->GetRotation(),
			scale,
			&currTexture->rectRgn,		//�ü�����
			Vector2(0, 0)* scale,	//ƫ��
			false, false);	//X��Y�������Ƿ�ת
	}
}
