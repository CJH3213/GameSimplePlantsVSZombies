#include "TextureRender.h"
#include "Game.h"

TextureRender::TextureRender(Texture* texture, int drawOrder) :
	mTexture(texture), mDrawOrder(drawOrder)
{
}

TextureRender::~TextureRender()
{
	// 将当前组件与渲染组件分离
	GetGame()->mRenderManager->RemoveComponent(this);
	// Texture对象是要析构的，但是里面的sdlTexture不要手动析构
	delete mTexture;	
}

ComponentBase* TextureRender::Clone() const
{
	// 我知道const_cast不是很好的办法，先用着吧
	auto game = const_cast<TextureRender*> (this)->GetGame();
	// 拷贝纹理
	Texture* copyTexture = game->mImageManagement->
		CopyTexture(mTexture);
	TextureRender* newComp = new TextureRender(copyTexture, mDrawOrder);
	newComp->mOffset = mOffset;
	return newComp;
}

void TextureRender::Awake()
{
	//将渲染组件添加到渲染管理器
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

		// 如果渲染器找到当前组件，更新顺序；
		// 如果渲染器没有找到组件，说明组件未添加，待组件初始化时会添加并排序
		GetGame()->mRenderManager->ChangeDrawOrder(this);
	}
}

void TextureRender::ChangeTexture(Texture* texture)
{
	// 先析构原有纹理
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
		// 纹理存在才绘制，否则渲染器会显示灰色矩形
		if (mTexture != nullptr)
		{
			//获取游戏对象空间信息
			auto transform = GetTransform();
			Vector2 scale = transform->GetScale();

			// 获取纹理左上角坐标
			Vector2 leftTopPos = transform->GetPosition() - 
				mTexture->GetSize() * scale / 2;

			// 将纹理复制到渲染器上
			w->CopyTextureToRenderer(mTexture,
				leftTopPos,
				transform->GetRotation(),
				scale,
				&mTexture->rectRgn,		//裁剪区域
				mOffset * scale,	//偏移
				false, false);	//X、Y方向上是否翻转
		}
	}
}

int TextureRender::GetDrawOrder() const
{
	return mDrawOrder;
}
