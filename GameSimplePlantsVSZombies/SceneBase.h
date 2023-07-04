#pragma once
#include <vector>
#include "GameObject.h"
#include "Prefab.h"

/// <summary>
/// ���������ࣩ��
/// ���ɵ�ǰ�ؿ���������������Ϸ����
/// </summary>
class SceneBase    //������̳���GameObject
    : public Object   //�������ϼ������ǹ���������Game�أ�
{
private:
    // ��������
    std::string mName;

public:
    // ��Ϸ����
    class Game* mGame = nullptr;
    // ����ִ���߼����±�־
    bool mIsUpdating = false;
    // ����Ч��Ϸ��������
    std::vector<GameObject*> mGameObjects;
    // ����δ������Ϸ��������
    std::vector<GameObject*> mPendingGameObjects;

    // ���캯��
    SceneBase(std::string name);
    // ��������
    ~SceneBase();

    // ��ȡ������
    std::string GetName() const { return mName; };

    // �����Ϸ����
    void AddGameObject(GameObject* gObj);
    // ���Ԥ�Ƽ�����
    void AddGameObject(Prefab* gObj);
    // ��Ӷ����Ϸ����
    template<typename T>
    void AddGameObjects(const T& gObjs);
    // �Ƴ���Ϸ����
    void RemoveGameObject(GameObject* gObj);
    // ͨ�����ֲ��Ҷ���
    GameObject* FindGameObject(std::string name);

    //��ͣ����
    void Paused();

    // �������غ�ʵ��������
    virtual void Start() {};

    // ��ȡ��Ϸ����
    class Game* GetGame() { return mGame; }

};

template<typename T>
inline void SceneBase::AddGameObjects(const T& gObjs)
{
    for (auto& obj : gObjs)
        AddGameObject(obj);
}
