#include "SpriteAnimator.h"
#include "Game.h"
#include "Time.h"

SpriteAnimator::~SpriteAnimator()
{
	// 将当前组件与渲染组件分离
	GetGame()->mRenderManager->RemoveComponent(this);
	// 销毁所有纹理
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
		// 将一组动画中的纹理部分提取出来
		textures.clear();
		for (auto& key : map.second)
			textures.emplace_back(key.texture);

		// 拷贝纹理组
		newComp->AddTextures(map.first,
			const_cast<SpriteAnimator*>(this)->GetGame()->
			mImageManagement->CopyTextures(textures));

		// 寻找播放动作组名称
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
		// 如果当前播放的和设定相同，则不必重头播放
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
	//将渲染组件添加到渲染管理器
	GetGame()->mRenderManager->AddComponent(this);
}

void SpriteAnimator::Update()
{
	if (mPlaying != nullptr)
	{
		// 获取已经播放时间
		float deltaTime = Time::Time_s() - mTimeLast;
		mTimeLast = Time::Time_s();
		// 算出现在播放到第几帧
		float nextFrame = mCurrFrame;
		mCurrFrame += mAnimFPS * deltaTime;

		// 检测是否已经换了一帧
		bool change = false;
		if ((int)mCurrFrame != (int)nextFrame)
			change = true;

		// 求余，使当前帧数在总张数之内
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
		// 获取当前纹理
		Texture* currTexture = (*mPlaying)[mCurrFrame].texture;

		//获取游戏对象空间信息
		auto transform = GetTransform();
		Vector2 scale = transform->GetScale();

		// 获取纹理左上角坐标
		Vector2 leftTopPos = transform->GetPosition() -
			currTexture->GetSize() * scale / 2;

		// 将纹理复制到渲染器上
		w->CopyTextureToRenderer(currTexture,
			leftTopPos,
			transform->GetRotation(),
			scale,
			&currTexture->rectRgn,		//裁剪区域
			Vector2(0, 0)* scale,	//偏移
			false, false);	//X、Y方向上是否翻转
	}
}
