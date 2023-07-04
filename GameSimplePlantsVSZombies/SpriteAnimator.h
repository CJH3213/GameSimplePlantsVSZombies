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
	// �ؼ�֡
	struct Keyframe
	{
		// ִ������ʱ��
		Texture* texture = nullptr;
		// �ص�����
		std::function<void()> action = [] {};
	};
	// ������
	struct KeyAction
	{
		int frameIndex = 0;
		std::function<void()> action = [] {};
	};

private:
	// �ٶ�
	int mAnimFPS = 10;
	// ���ż�ʱ
	//float mTimeBegin = 0.0f;
	// ��һ֡ʱ��
	float mTimeLast = 0.0f;
	// ��ǰ֡��ʹ�ø����������ۼ�ƫ�
	float mCurrFrame = 0;
	// ��ǰ������
	std::vector<Keyframe>* mPlaying = nullptr;

	// ֡����������
	std::unordered_map<std::string, std::vector<Keyframe>>	 mTextures;

public:

	// ��Ⱦ�㼶����ȣ�
	int mDrawOrder = 100;

	// ����
	~SpriteAnimator();
	// ���
	virtual ComponentBase* Clone() const override;

	// ���֡������
	void AddTextures(std::string name, const std::vector<Texture*>& textures);
	// �Ƴ�֡������
	void RemoveTextures(std::string name);
	// ��ӻص��¼�
	void AddActions(std::string name, const std::vector<KeyAction>& actions);

	// ���ò���֡��
	void SetFPS(int fps) { mAnimFPS = fps; }
	// ���Ŷ�����
	void Play(std::string name);
	// ���²��ŵ�ǰ������
	void RePlay();
	// ֹͣ����
	void Stop();

	// �����ʼ
	virtual void Awake() override;
	// �������
	virtual void Update() override;

	/******************��Ⱦ�ӿ�ʵ��******************/
	// �Ƿ�������Ⱦ
	virtual bool IsRenderEnable() override { return IsEnable(); }
	// ��ȡ���Ʋ㼶
	virtual int GetDrawOrder() const  override { return mDrawOrder; }
	// ���ƽӿ�
	virtual void OnRender(Window* w) override;
};

