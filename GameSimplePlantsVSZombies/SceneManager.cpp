#include "SceneManager.h"

void SceneManager::LoadScene(SceneBase* scene)
{
        //���泡��������
        mPendingScenes.push_back(scene);
}

SceneBase* SceneManager::GetActivityScene()
{
    return mActivityScene;
}

SceneBase* SceneManager::GetSceneAt(int index)
{
    if (index < mScenes.size())
        return mScenes[index];

    return nullptr;
}

SceneBase* SceneManager::GetSceneByName(std::string name)
{
    for (auto& scene : mScenes)
    {
        if (scene->GetName() == name)
            return scene;
    }

    return nullptr;
}

void SceneManager::OnGameLoop_Pre()
{
    // ���ֻ�Ծ������ǰ�ø���
    if (mActivityScene)
    {
        auto& pendingObjs = mActivityScene->mPendingGameObjects;
        auto& objs = mActivityScene->mGameObjects;

        // ������Ľ�ɫ�ƶ��������
        for (auto pending : pendingObjs)
            objs.emplace_back(pending);
        pendingObjs.clear();

        // ���������Ľ�ɫ����
        for (auto iter = objs.begin(); iter != objs.end();)
        {
            if ((*iter)->mState == GameObject::EDead)
            {
                delete (*iter);
                iter = objs.erase(iter);
            }
            else
                iter++;
        }

        // ������ɫ��Ԥ���£�֡ǰ���£�
        for (auto obj : objs)
            obj->PreUpdate();
    }

    // ������ĳ���ת�Ƶ���ʽ��������
    if (mPendingScenes.size() > 0)
    {
        // �����ϴλ�Ծ��������ʱûʵ�ֳ�����ͣ����
        auto iter = std::find(mScenes.begin(), mScenes.end(), mActivityScene);
        if (iter != mScenes.end())
        {
            mScenes.erase(iter);
            delete mActivityScene;
        }

        // �����ת��
        for (auto& scene : mPendingScenes)
        {
            mScenes.emplace_back(scene);
            scene->mGame = mGame;
            scene->Start(); //������ʼ��
        }
        mPendingScenes.clear();

        //�´λ�Ծ����Ϊ�������һ������������ʱ�����ɣ�һ����Ӷ������Ҳûɶ���壩
        mActivityScene = *(mScenes.end() - 1);
    }

}

void SceneManager::OnGameLoop_Update()
{
    if (mActivityScene != nullptr)
    {
        auto& objs = mActivityScene->mGameObjects;

        //ִ�����л�Ծ���������ĸ���
        for (auto obj : objs)
        {
            if(obj->GetActive())
                obj->Update();
        }

        //�ӳٸ���
        for (auto obj : objs)
        {
            if (obj->GetActive())
                obj->LateUpdate();
        }
    }
}
