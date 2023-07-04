#pragma once
#include "ComponentBase.h"
#include <vector>
#include <unordered_map>
#include "Vector2.h"
#include <functional>

/// <summary>
/// �������
/// </summary>
class Animator
	: public ComponentBase
{
private:
	// �ؼ�֡
	struct Keyframe
	{
		// ִ������֡
		//uint16_t frameNum = 0;
		// ִ������ʱ��
		float time = 0.0f;
		// �任״̬
		Vector2 position = { 0.0f, 0.0f };
		float rotation = 0.0f;
		Vector2 scale = { 1.0f, 1.0f };
		// �ص�����
		std::function<void()> action = [] {};
	};

private:
	// �����ٶȣ���ʱ��֪����ôʵ�ֱ��ٺ͵���
	float mSpeed = 1.0f;

	// �ֲ���֡����
	//uint16_t mFrameCount = 0;
	// ���ż�ʱ
	float mTimeBegin = 0.0f;
	// ���ڲ��ŵĶ�����
	std::vector<Keyframe>* mPlaying = nullptr;
	// ��һ�ؼ�֡����������
	size_t mKeyIndex = 0;

	// �˶��ؼ�֡
	std::unordered_map<std::string, std::vector<Keyframe>> mKeyframes;

public:

	// ���
	virtual ComponentBase* Clone() const override;

	// ��Ӷ�����
	void AddKeyframe(std::string name, const std::vector<Keyframe>& frames);
	// �Ƴ�������
	void RemoveKeyframe(std::string name);

	// ���Ŷ�����
	void Play(std::string name);
	// ֹͣ����
	void Stop();
	// ���²��ŵ�ǰ������
	void RePlay();

	// �������
	virtual void Update() override;
};

