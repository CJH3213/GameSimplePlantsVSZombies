#pragma once
#include "Vector2.h"
#include "ICollider.h"

class IPointer
{
public:
    // ��� �ص�
    virtual void OnMouseCallback(Vector2) = 0;
    // �������������
    virtual void LateMouseUpdate(Vector2)  = 0;

    //// �����������ײ���Ϸ��ĵ�һ֡���ǵ����
    //virtual void OnMouseEnter(Vector2) {};
    //// ��������������ײ����ÿһ֡���ǵ����
    //virtual void OnMouseOver(Vector2) {};
    //// ��������Ƴ���ײ��ʱ���һ֡���ǵ����
    //virtual void OnMouseExit(Vector2) {};
    //// �������ײ���ĵ�һ֡�������
    //virtual void OnMouseDown(Vector2) {};
    //// �������ײ���ĵ�һ֡�������
    //virtual void OnMouseDrag(Vector2) {};
    //// �������ײ���ĵ�һ֡�������
    //virtual void OnMouseUp(Vector2) {};
    //// ��������ͷŶ��ڰ����ϣ������
    //virtual void OnMouseUpAsButton(Vector2) {};

    // ��ȡ��ײ�������ص���Ϸ����
    virtual class GameObject* GetGameObj() = 0;
    // ����Ƿ�����һ����ײ���ཻ
    virtual bool IsIntersectWithPoint(const Vector2&) = 0;
};

