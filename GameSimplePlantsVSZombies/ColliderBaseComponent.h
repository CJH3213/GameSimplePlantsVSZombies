#pragma once
#include "ComponentBase.h"
#include "IRenderer.h"
#include "ICollider.h"
#include <functional>
#include "Rectangle.h"
#include <map>


class ColliderBaseComponent :
    public ComponentBase, ICollider, IRenderer
{
private:
    // ��ײǰ��֡״̬
    struct CollisionInfo
    {
        bool mPrevState = false;
        bool mCurrState = false;
    };

    // ��¼�ཻ��ײ���ϴ���ײ״̬
    std::map<ICollider*, CollisionInfo> mRecords;
    // ��¼��������ײ״̬
    CollisionInfo mMouseHover = { false, false };
    CollisionInfo mMouseClick = { false, false };

public:
    //�Ƿ�Ϊ�����������������Դ�͸����ײ�䲻�ܴ�͸
    bool isTrigger = false;
    //��Χ��
    Rectangle mBounds;

    //����
    ColliderBaseComponent(std::string name);
    //����
    virtual ~ColliderBaseComponent();

    //��ʼ��
    virtual void Awake() override;

    /******************��Ⱦ�ӿ�ʵ��******************/
    // ���ư�Χ��
    virtual void OnRender(Window* w) override;

    /******************��ײ�ӿ�ʵ��******************/
    // ��ײ�����������
    virtual void LateCollideUpdate() override;
    // ��ײ�ص�����
    virtual void OnCollisionCallback(ICollider*) override;

    // �����ཻ�ص�
    virtual void OnCollisionEnter(ICollider*)  override {};
    // �����ཻ�ص�
    virtual void OnCollisionStay(ICollider*)  override {};
    // �����ཻ�ص�
    virtual void OnCollisionExit(ICollider*)  override {};

    // ��ȡ��ײ�������ص���Ϸ����
    virtual class GameObject* GetGameObj() override;
    // ��ȡ��ǰ��ײ���İ�Χ��
    virtual Rectangle& GetBounds() override;
    // ����Ƿ�����һ����ײ���ཻ
    virtual bool IsIntersectWithAABB(Rectangle&) override;
};

///*��ײ�㷨*/
////��������Ƿ��غ�
//static bool CheckPointWithPoint(Vector2& point1, Vector2& point2);
//
////���Բ����Բ���Ƿ���ײ
//static bool CheckCircleWithCircle(class CircleColliderComponent* circle1, class CircleColliderComponent* circle2);
////���Բ������Ƿ���ײ
//static bool CheckCircleWithPoint(class CircleColliderComponent* circle, Vector2& point);
//
////��������������Ƿ���ײ
//static bool CheckBoxWithBox(class BoxColliderComponent* box1, BoxColliderComponent* box2);
////�����������Ƿ���ײ
//static bool CheckBoxWithPoint(class BoxColliderComponent* box, Vector2& point);
////���������Բ���Ƿ���ײ
//static bool CheckBoxWithCircle(class BoxColliderComponent* box, class CircleColliderComponent* circle);
