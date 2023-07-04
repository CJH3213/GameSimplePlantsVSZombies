#pragma once
#include "GameObject.h"
#include "SpriteGameObject.h"

class ProgressGameObject :
    public GameObject
{
private:
    //进度：0.0~1.0
    float progress = 0.0f;

    //底图
    SpriteGameObject* backgroundSprite = nullptr;
    //进度条图
    SpriteGameObject* barSprite = nullptr;
    //进度点图
    SpriteGameObject* pointSprite = nullptr;

public:
    //构造析构
    ProgressGameObject(string name, class GameObject* go, int drawOrder);
    ~ProgressGameObject();

    //设置进度：1.0f代表100%
    void SetProgress(float f);
    //设置底图对象
    void SetBackGroundSprite(SpriteGameObject* sgo);
    //设置进度条图对象
    void SetBarSprite(SpriteGameObject* sgo);
    //设置进度点图对象
    void SetPointSprite(SpriteGameObject* sgo);
};

