#pragma once
#include "ComponentBase.h"
#include "ICollider.h"
#include <map>
#include <array>
#include "EventHandlers.h"
#include "IRenderer.h"

class ColliderBase :
    public ComponentBase, public ICollider, public IRenderer
{
private:
	// ��¼��֮��ײ�������״̬
	std::map<ICollider*, std::array<bool, 2>> mCollisionState;

	// ����ָ����ײ����¼
	void RemoveColliderRecord(ICollider* other);

public:
	// ������ײ���������ƫ����
	Vector2 mOffset;

	// ��ײ�����¼��ص�
	EventHandlers<void(ICollider*)> mEnterEvents;
	// ��ײ�����¼��ص�
	EventHandlers<void(ICollider*)> mStayEvents;
	// ��ײ�����¼��ص�
	EventHandlers<void(ICollider*)> mExitEvents;

	/******************�ű���������******************/
	// ��������
	~ColliderBase();

	// �����ʼ��
	virtual void Awake() override;
	// ���á�����
	//virtual void OnEnable() {};
	virtual void OnDisable();

	/******************��ײ�ӿ�ʵ��******************/
	// �Ƿ�������ײ
	virtual bool IsColliderEnable() override { return IsEnable(); }
	// ��ײ�ص�����
	virtual void OnCollisionCallback(ICollider*) override;
	// ��ײ�����������
	virtual void LateCollideUpdate() override;
	// ��ȡ��ײ�������ص���Ϸ����
	virtual class GameObject* GetGameObj() override;

	/******************��Ⱦ�ӿ�ʵ��******************/
	// �Ƿ�������Ⱦ
	virtual bool IsRenderEnable() override { return IsEnable(); }
	// ���û��Ʋ㼶
	virtual int GetDrawOrder() const override { return 1; }
	// ��Ⱦ�ص�
	virtual void OnRender(Window* w) override;

	/******************�Զ��巽��******************/
	// ��ȡ��ײ��¼��
	const std::map<ICollider*, std::array<bool, 2>>& GetCollisionState() { return mCollisionState; }
};

