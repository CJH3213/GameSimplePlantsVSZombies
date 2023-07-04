#pragma once
#include "Object.h"

/// <summary>
/// ��������ࣩ��
/// ����Ϸ����Ĳ��ֹ��ܷ�װ��һ�������
/// </summary>
class ComponentBase
     : public Object    //�̳�Ȩ��public���߲��ܷ��ʳ�Ա
{
protected:
    // �Դ��������ƶ�
    ComponentBase(const ComponentBase&) = default;
    ComponentBase& operator=(const ComponentBase&) = default;
    ComponentBase(ComponentBase&&) = default;
    ComponentBase& operator=(ComponentBase&&) = default;

protected:
    // ���ʹ��/����
    bool mIsEnable = true;
    // ���������Ϸ����
    class GameObject* mGameObject = nullptr;

    //����Ƿ��Ѿ�ִ�й�Start����
    bool mIsStarted;

public:
    // ���캯�������ö������ͳ����������Ϸ����
    ComponentBase();
    // ��������������������������Ϊ�麯��
    virtual ~ComponentBase();
    // �ֶ�ʵ�����
    virtual ComponentBase* Clone() const { return nullptr; }

    // ���ò������Ϸ��������ע�룩
    void SetOwner(class GameObject* obj);
    // ���������Ծ/����
    void SetEnable(bool b);
    // ��ȡ��Ծ״̬
    bool IsEnable() const { return mIsEnable; }


    /*�̳е�����ṩ��������*/
    // ��ӵ���Ϸ��������һ��
    virtual void Awake(){}
    // ��һ�ε���Updateǰִ��һ��
    virtual void Start(){}
    
    // �߼����£���������ã���Ҫ��д���������
    void _Update();
    // �߼����º�
    virtual void LateUpdate(){}

    // ��Ⱦ����
    virtual void OnRendering(){}

    // �̶��������
    virtual void FixedUpdate(){}

    // ����ǰ
    virtual void Destroy(){}


    // ��ȡGame����
    class Game* GetGame();
    // ��ȡ��������
    class SceneBase* GetScene();
    // ��ȡ������ڵ���Ϸ����
    class GameObject* GetGameObject() { return mGameObject; }
    // ��ȡTransform���
    class TransformComponent* GetTransform();

protected:
    // �߼����£����û���д��
    virtual void Update() {}
    // ���á�����
    virtual void OnEnable(){}
    virtual void OnDisable(){}

    // ʵ����Ԥ�Ƽ�
    template<typename T>
    T* Instantiate(T* obj, TransformComponent* parent);
    // ����������Ϸ����
    void Destroy(class GameObject* gObj);
    // ���������Ӷ��󣨲�������ǰ����
    void DestroyAllChildren(class GameObject* gObj);
};

template<typename T>
inline T* ComponentBase::Instantiate(T* obj, TransformComponent* parent)
{
    GetScene()->AddGameObject(obj);		// ��������ӵ���ǰ����
    obj->mTransform->SetParent(parent);	// ���ø���ϵ

    return obj;
}
