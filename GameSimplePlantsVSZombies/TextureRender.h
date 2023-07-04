#pragma once
#include "ComponentBase.h"
#include "IRenderer.h"

class TextureRender :
    public ComponentBase, public IRenderer
{
private:
    // ͼ��·��
    //std::string mImgPath = "";
    // ���Ʋ㼶��ֵԽС�����Խ����
    int mDrawOrder;

public:
    //����
    Texture* mTexture = nullptr;
    //ƫ��
    Vector2 mOffset;

    //���캯��
    TextureRender(Texture* texture, int drawOrder = 100);
    //��������
    ~TextureRender();
    // ���
    virtual ComponentBase* Clone() const override;

    //�����ʼ��
    virtual void Awake() override;

    // ���û��Ʋ㼶�����ٶ�̬�����Խ��Ͷ��⿪��������Ҫ���ã�����bugû���
    void SetDrawOrder(int drawOrder);
    // �ı�����ͼƬ
    void ChangeTexture(std::string imgPath);
    void ChangeTexture(Texture* texture);
    // ����͸��ͨ��
    void SetAlpha(float alpha);

    // �Ƿ�������Ⱦ
    virtual bool IsRenderEnable() override { return IsEnable(); }
    // �ṩ��Ⱦ��������ȡ��Ⱦ��ȣ�����˳��
    virtual int GetDrawOrder() const override;
    // ����Ⱦ�����õ�Draw����
    virtual void OnRender(Window* w) override;
};

