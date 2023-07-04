#pragma once
#include "ComponentBase.h"
#include "IPointer.h"
#include "IRenderer.h"
#include "EventHandlers.h"
#include "Vector2.h"

class Button :
    public ComponentBase, public IPointer, public IRenderer
{
protected:
    // ��¼���״̬
    bool mMouseHover[2] = { false, false };
    bool mMouseClick[2] = { false, false };

public:
    // ��ײ�д�С
    Vector2 mSize = { 10, 10 };
    // ������ƫ��
    Vector2 mOffset;

    // ��������
    ~Button();
    // ���
    virtual ComponentBase* Clone() const override;

    // �����ʼ��
    virtual void Awake() override;

    // ��ȡ��ǰ��ײ���İ�Χ��
    Rectangle GetBounds();

    /******************�����ײ�ӿ�ʵ��******************/
        // ��� �ص�
    virtual void OnMouseCallback(Vector2 pos) override;
    // �������������
    virtual void LateMouseUpdate(Vector2 pos) override;

    // ��ȡ��ײ�������ص���Ϸ����
    virtual class GameObject* GetGameObj() override;
    // ����Ƿ�����һ����ײ���ཻ
    virtual bool IsIntersectWithPoint(const Vector2& pos) override;

    // �����������ײ���Ϸ��ĵ�һ֡���ǵ����
    EventHandlers<void()> mMouseEnterEvents;
    // ��������������ײ����ÿһ֡���ǵ����
    EventHandlers<void()> mMouseOverEvents;
    // ��������Ƴ���ײ��ʱ���һ֡���ǵ����
    EventHandlers<void()> mMouseExitEvents;
    // �������ײ���ĵ�һ֡�������
    EventHandlers<void()> mMouseDownEvents;
    // �������ײ���ĵ�һ֡�������
    EventHandlers<void()> mMouseDragEvents;
    // �������ײ���ĵ�һ֡�������
    EventHandlers<void()> mMouseUpEvents;
    // ��������ͷŶ��ڰ����ϣ������
    EventHandlers<void()> mMouseUpAsButtonEvents;
    EventHandlers<void()>& OnClick = mMouseUpAsButtonEvents;

    /******************��Ⱦ�ӿ�ʵ��******************/
    virtual bool IsRenderEnable() override{ return IsEnable(); }
    virtual void OnRender(Window* w) override;
};

