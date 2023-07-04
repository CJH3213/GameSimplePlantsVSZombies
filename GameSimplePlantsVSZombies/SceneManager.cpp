#include "SceneManager.h"

void SceneManager::LoadScene(SceneBase* scene)
{
        //保存场景到容器
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
    // 对现活跃场景作前置更新
    if (mActivityScene)
    {
        auto& pendingObjs = mActivityScene->mPendingGameObjects;
        auto& objs = mActivityScene->mGameObjects;

        // 将挂起的角色移动到活动容器
        for (auto pending : pendingObjs)
            objs.emplace_back(pending);
        pendingObjs.clear();

        // 将已死亡的角色销毁
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

        // 场景角色的预更新（帧前更新）
        for (auto obj : objs)
            obj->PreUpdate();
    }

    // 将挂起的场景转移到正式场景容器
    if (mPendingScenes.size() > 0)
    {
        // 销毁上次活跃场景，暂时没实现场景暂停功能
        auto iter = std::find(mScenes.begin(), mScenes.end(), mActivityScene);
        if (iter != mScenes.end())
        {
            mScenes.erase(iter);
            delete mActivityScene;
        }

        // 挂起的转正
        for (auto& scene : mPendingScenes)
        {
            mScenes.emplace_back(scene);
            scene->mGame = mGame;
            scene->Start(); //场景初始化
        }
        mPendingScenes.clear();

        //下次活跃场景为容器最后一个场景（先暂时这样吧，一次添加多个场景也没啥意义）
        mActivityScene = *(mScenes.end() - 1);
    }

}

void SceneManager::OnGameLoop_Update()
{
    if (mActivityScene != nullptr)
    {
        auto& objs = mActivityScene->mGameObjects;

        //执行所有活跃对象的组件的更新
        for (auto obj : objs)
        {
            if(obj->GetActive())
                obj->Update();
        }

        //延迟更新
        for (auto obj : objs)
        {
            if (obj->GetActive())
                obj->LateUpdate();
        }
    }
}
