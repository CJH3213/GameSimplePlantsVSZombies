#include "TextureRender.h"
#include "Game.h"

TextureRender::TextureRender(Texture* texture, int drawOrder) :
	mTexture(texture), mDrawOrder(drawOrder)
{
}

TextureRender::~TextureRender()
{
	// ����ǰ�������Ⱦ�������
	GetGame()->mRenderManager->RemoveComponent(this);
	// Texture������Ҫ�����ģ����������sdlTexture��Ҫ�ֶ�����
	delete mTexture;	
}

ComponentBase* TextureRender::Clone() const
{
	// ��֪��const_cast���Ǻܺõİ취�������Ű�
	auto game = const_cast<TextureRender*> (this)->GetGame();
	// ��������
	Texture* copyTexture = game->mImageManagement->
		CopyTexture(mTexture);
	TextureRender* newComp = new TextureRender(copyTexture, mDrawOrder);
	newComp->mOffset = mOffset;
	return newComp;
}

void TextureRender::Awake()
{
	//����Ⱦ�����ӵ���Ⱦ������
	GetGame()->mRenderManager->AddComponent(this);
}

void TextureRender::ChangeTexture(std::string imgPath)
{
	ChangeTexture(
		GetGame()->mImageManagement->GetTextureByPath(imgPath)
		);
}

void TextureRender::SetDrawOrder(int drawOrder)
{
	if(drawOrder != mDrawOrder)
	{
		mDrawOrder = drawOrder;

		// �����Ⱦ���ҵ���ǰ���������˳��
		// �����Ⱦ��û���ҵ������˵�����δ��ӣ��������ʼ��ʱ����Ӳ�����
		GetGame()->mRenderManager->ChangeDrawOrder(this);
	}
}

void TextureRender::ChangeTexture(Texture* texture)
{
	// ������ԭ������
	delete mTexture;

	mTexture = texture;
}

void TextureRender::SetAlpha(float alpha)
{
	mTexture->SetTextureAlpha(alpha * 255);
}

void TextureRender::OnRender(Window* w)
{
	if (mIsEnable)
	{
		// ������ڲŻ��ƣ�������Ⱦ������ʾ��ɫ����
		if (mTexture != nullptr)
		{
			//��ȡ��Ϸ����ռ���Ϣ
			auto transform = GetTransform();
			Vector2 scale = transform->GetScale();

			// ��ȡ�������Ͻ�����
			Vector2 leftTopPos = transform->GetPosition() - 
				mTexture->GetSize() * scale / 2;

			// �������Ƶ���Ⱦ����
			w->CopyTextureToRenderer(mTexture,
				leftTopPos,
				transform->GetRotation(),
				scale,
				&mTexture->rectRgn,		//�ü�����
				mOffset * scale,	//ƫ��
				false, false);	//X��Y�������Ƿ�ת
		}
	}
}

int TextureRender::GetDrawOrder() const
{
	return mDrawOrder;
}
