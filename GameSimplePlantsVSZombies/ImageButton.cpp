#include "ImageButton.h"
#include "GameObject.h"
#include "Game.h"
#include "Input.h"

ImageButton::ImageButton(
	std::string normalPath,
	std::string highLigPath,
	std::string pressedPath)
{
	mNormalImgPath = normalPath;
	mHighLigImgPath = highLigPath;
	mPressedImgPath = pressedPath;
}

ImageButton::~ImageButton()
{
	delete mNormalTex;
	mNormalTex = nullptr;

	delete mHighLigTex;
	mHighLigTex = nullptr;

	delete mPressedTex;
	mPressedTex = nullptr;
}

ComponentBase* ImageButton::Clone() const
{
	ImageButton* newComp = 
		new ImageButton(mNormalImgPath, mHighLigImgPath, mPressedImgPath);
	// 复制图片资源路径

	// 纹理要重新生成不要复制指针
	// 待新的组件运行到Awake时，就会重新加载纹理

	return newComp;
}

void ImageButton::Awake()
{
	// 先执行父组件初始化
	Button::Awake();

	// 通过路径加载纹理
	auto& imgManager = GetGame()->mImageManagement;
	mNormalTex = imgManager->GetTextureByPath(mNormalImgPath);
	mHighLigTex = imgManager->GetTextureByPath(mHighLigImgPath);
	mPressedTex = imgManager->GetTextureByPath(mPressedImgPath);
	// 初始渲染目标为未按下的按钮纹理
	mRenderTex = mNormalTex;

	// 初始包围盒
	if(mRenderTex)
		mSize = mRenderTex->GetSize() * GetTransform()->GetScale();

	// 注册鼠标回调事件
	mMouseEnterEvents.AddListener("_BtnEnter", std::bind(&ImageButton::OnMouseEnter, this));
	mMouseExitEvents.AddListener("_BtnExit", std::bind(&ImageButton::OnMouseExit, this));
	mMouseDownEvents.AddListener("_BtnDown", std::bind(&ImageButton::OnMouseDown, this));
	mMouseUpAsButtonEvents.AddListener("_BtnUp", std::bind(&ImageButton::OnClickDown, this));

}

void ImageButton::Update()
{
	mSize = mRenderTex->GetSize();
}

void ImageButton::OnMouseEnter()
{
	if(mHighLigTex)
		mRenderTex = mHighLigTex;
}

void ImageButton::OnMouseExit()
{
	mRenderTex = mNormalTex;
}

void ImageButton::OnMouseDown()
{
	if(mPressedTex)
		mRenderTex = mPressedTex;
}

void ImageButton::OnClickDown()
{
	// 鼠标在按钮上释放时，恢复高光纹理
	if(mHighLigTex)
	mRenderTex = mHighLigTex;
}

void ImageButton::OnRender(Window* w)
{
	if (mRenderTex != nullptr)
	{
		//获取游戏对象空间信息
		auto trans = mGameObject->mTransform;

		//调用纹理渲染接口，绘制到窗体上
		Vector2 leftTopPos = trans->GetPosition() -
			mRenderTex->GetSize() * trans->GetScale() / 2;

		w->CopyTextureToRenderer(mRenderTex,
			leftTopPos,
			trans->GetRotation(),
			trans->GetScale(),
			&mRenderTex->rectRgn,		//裁剪区域
			{ 0, 0 },	//偏移
			false, false);	//X、Y方向上是否翻转

		// 绘制包围盒
		w->SetPenColor(255, 255, 0, 255);
		w->DrawRectangle(GetBounds());
	}
}
