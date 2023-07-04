#pragma once
#include <vector>
#include "TransformComponent.h"

/// <summary>
/// ��Ϸ���󣨻��ࣩ��
/// </summary>
class GameObject
     :public Object
{
protected:
    // ����/����״̬
    bool mIsActive = true;
    //���ڵĳ���
    class SceneBase* mScene = nullptr;
    //��ǰ��Ϸ����������������Ծ�����
    std::vector<ComponentBase*> mComponents;
    // ��ӵ���Ϸ����δ��ʼ����������������
    std::vector<ComponentBase*> mPendingComponents;

public:
    // ״̬ö��
    enum State
    {
        EActive,    //��Ծ������
        EPaused,    //��ͣ��������
        EDead   //����������
    };
    // ��ɫ״̬
    State mState;

    // �任�����������Ϸ�����һ���任�����
    TransformComponent* mTransform = nullptr;
    // �����ǩ
    std::string mTag ;// = "Untagged";
    // ��������
    std::string mName ;

    // ���캯�������ö������ͳ����������Ϸ����
    GameObject(std::string name, std::string tag);
    GameObject(std::string name);
    // ��������������������������Ϊ�麯��
    ~GameObject();
    // �������
    GameObject(const GameObject& other);

    // ��ȡ������
    std::string GetName() const { return mName; }
    // ���ö�������/����
    void SetActive(bool b);
    // ��ȡ�����Ծ״̬
    bool GetActive() const { return mIsActive; }

    // Ԥ����
    virtual void PreUpdate();
    // �߼�����
    void Update();
    // �ӳ��߼�����
    void LateUpdate();

    // ���ø�����
    void SetParent(GameObject* obj);
    // ��ӣ����룩�����������
    void AddComponent(ComponentBase* comp);
    // ���������Ƴ�ָ�����
    void RemoveComponent(ComponentBase* comp);
    // ���������Ƴ�ָ�����Ƶ����
    // void RemoveComponent(std::string name);

    // ���ó�������
    void SetScene(class SceneBase* s) { mScene = s; }
    // ��ȡ��������
    class SceneBase* GetScene(){ return mScene; }
    // ��ȡ��Ϸ������Ϸ�����ģ�
    class Game* GetGame();

public:
    // �������л�ȡһ��ָ�����͵����
    template<typename T>
    T* GetComponent();
    // �Ӷ����������л�ȡһ��ָ�����͵����
    template<typename T>
    static T* GetComponentInChildren(TransformComponent* trans);
    // �Ӷ����������л�ȡһ��ָ�����͵����
    template<typename T>
    T* GetComponentInChildren();
};

//ģ�庯�������ͱ����ڱ����ڼ��ȷ�������Ժ����������ͷ�ļ�������CPP�ļ����������ͷ�ļ�����Ҫinline��������
//��ģ�庯���Ķ������cpp�ļ��ڣ������ڼ��ģ�庯��ֻ�ܻ�ȡ����ǰ������ͣ�������������ǻ�ȡ�����ġ�
// �������л�ȡһ��ָ�����͵����
template<typename T>
T* GameObject::GetComponent()
{
    // �ӻ�Ծ�����������
    for (auto it = mComponents.begin(); it != mComponents.end(); it++)
    {
        if (typeid(T).name() == (*it)->GetClassInfo().name())
        {
            return dynamic_cast<T*> (*it);  //����ת������
        }  
    }
    // �ӹ��������������
    for (auto it = mPendingComponents.begin(); it != mPendingComponents.end(); it++)
    {
        if (typeid(T).name() == (*it)->GetClassInfo().name())
        {
            return dynamic_cast<T*> (*it);  //����ת������
        }
    }

    return nullptr;
}

// �Ӷ����������л�ȡһ��ָ�����͵����
template<typename T>
T* GameObject::GetComponentInChildren(TransformComponent* trans)
{
    // ���ڵ�ǰ�����в����Ƿ��и����
    T* comp = trans->GetGameObject()->GetComponent<T>();
    if (comp != nullptr)
        return comp;
    // ����������������
    else
    {
        for (int i = 0; i < trans->ChildCount(); i++)
        {
            T* comp = GetComponentInChildren<T>(trans->GetChild(i));
            if (comp != nullptr)
                return comp;
        }
    }

    return nullptr;
}

// �Ӷ����������л�ȡһ��ָ�����͵����
template<typename T>
T* GameObject::GetComponentInChildren()
{
    return GetComponentInChildren<T>(mTransform);
}