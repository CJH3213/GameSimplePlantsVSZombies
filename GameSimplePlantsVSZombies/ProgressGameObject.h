#pragma once
#include "GameObject.h"
#include "SpriteGameObject.h"

class ProgressGameObject :
    public GameObject
{
private:
    //���ȣ�0.0~1.0
    float progress = 0.0f;

    //��ͼ
    SpriteGameObject* backgroundSprite = nullptr;
    //������ͼ
    SpriteGameObject* barSprite = nullptr;
    //���ȵ�ͼ
    SpriteGameObject* pointSprite = nullptr;

public:
    //��������
    ProgressGameObject(string name, class GameObject* go, int drawOrder);
    ~ProgressGameObject();

    //���ý��ȣ�1.0f����100%
    void SetProgress(float f);
    //���õ�ͼ����
    void SetBackGroundSprite(SpriteGameObject* sgo);
    //���ý�����ͼ����
    void SetBarSprite(SpriteGameObject* sgo);
    //���ý��ȵ�ͼ����
    void SetPointSprite(SpriteGameObject* sgo);
};

