#pragma once
#include "Button.h"
#include "Texture.h"

class ImageButton :
    public Button
{
protected:
    // ��ť��ͨͼƬ
    std::string mNormalImgPath;
    Texture* mNormalTex = nullptr;
    // ��ť�߹�ͼƬ
    std::string mHighLigImgPath;
    Texture* mHighLigTex = nullptr;
    // ��ť��ѹͼƬ
    std::string mPressedImgPath;
    Texture* mPressedTex = nullptr;
    // ����ȾĿ������
    Texture* mRenderTex = nullptr;

public:

    // ���캯��
    ImageButton(
        std::string normalPath, 
        std::string highLigPath, 
        std::string pressedPath);
    // ��������
    ~ImageButton();
    // ���
    virtual ComponentBase* Clone() const override;

    // �����ʼ��
    virtual void Awake() override;
    // �������
    virtual void Update() override;

    // ������ص�
    void OnMouseEnter();
    // ����뿪�ص�
    void OnMouseExit();
    // ��갴�»ص�
    void OnMouseDown();
    // ��������ص�
    void OnClickDown();


    /******************��Ⱦ�ӿ�ʵ��******************/
    virtual void OnRender(Window* w) override;
};

