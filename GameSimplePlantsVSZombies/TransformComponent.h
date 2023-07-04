#pragma once
#include "ComponentBase.h"
#include "Vector2.h"
#include <vector>

//����ռ䣺��������
enum class Space : uint8_t  {Model, Self, Parent, World};

class TransformComponent :
    public ComponentBase
{
private:
    // �洢����ֱ���Ӷ���ı任���
    std::vector<TransformComponent*> mChildren;

public:
    Vector2 localPosition;       //�������
    float localRotation;     //��ԽǶ�
    Vector2 localScale;      //������ű�
    // ������ı任���
    TransformComponent* mParentTrans = nullptr;

    // ���캯����ȫ��������
    TransformComponent(TransformComponent* parentTrans,
        const Vector2& p, float r, const Vector2& s) ;
    // ���캯����ָֻ��λ�����꣬����ת��0�������ţ�1,1��
    TransformComponent(TransformComponent* parentTrans);
    // ���캯����ֻ���û��������Ϣ��������λ�ú͸�����
    TransformComponent();
    // ��������
    ~TransformComponent();
    // ���
    virtual ComponentBase* Clone() const override;

    // ��ȡ����λ��
    Vector2 GetPosition() const;
    // ��������λ��
    void SetPosition(Vector2 p);
    // ��ȡ������ת�Ƕ�
    float GetRotation() const;
    // ����������ת�Ƕ�
    void SetRotation(float r);
    // ��ȡ�������ű�
    Vector2 GetScale() const;
    // �����������ű�
    void SetScale(Vector2 v);

    // ִ��ǰ��׼��������������Ϸ����ʵ��������Ϊ����ĳ�ʼ��
    //virtual void Start() override;

    // �ƶ�����
    void Translate(float x, float y, Space relativeTo);
    void Translate(const Vector2& v, Space relativeTo);

    // ��ת����
    void Rotate(float angle, Space relativeTo);
    void RotateAround(float angle, const Vector2& v);
    bool LookAt(const Vector2& v);

    // ��������
    void Scale(const Vector2& v, Space relativeTo);
    void Scale(float f, Space relativeTo);


    /**********************�������ṩ�ڲ㼶����ķ���**************************/
    // ���ø���ϵ
    void SetParent(TransformComponent* parent);
    // ��ȡ�Ӷ�������
    size_t ChildCount();
    // ��ȡֱ���Ӷ���任���
    TransformComponent* GetChild(size_t index);
    
};

