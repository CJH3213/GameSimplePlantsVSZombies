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
	// ����ͼƬ��Դ·��

	// ����Ҫ�������ɲ�Ҫ����ָ��
	// ���µ�������е�Awakeʱ���ͻ����¼�������

	return newComp;
}

void ImageButton::Awake()
{
	// ��ִ�и������ʼ��
	Button::Awake();

	// ͨ��·����������
	auto& imgManager = GetGame()->mImageManagement;
	mNormalTex = imgManager->GetTextureByPath(mNormalImgPath);
	mHighLigTex = imgManager->GetTextureByPath(mHighLigImgPath);
	mPressedTex = imgManager->GetTextureByPath(mPressedImgPath);
	// ��ʼ��ȾĿ��Ϊδ���µİ�ť����
	mRenderTex = mNormalTex;

	// ��ʼ��Χ��
	if(mRenderTex)
		mSize = mRenderTex->GetSize() * GetTransform()->GetScale();

	// ע�����ص��¼�
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
	// ����ڰ�ť���ͷ�ʱ���ָ��߹�����
	if(mHighLigTex)
	mRenderTex = mHighLigTex;
}

void ImageButton::OnRender(Window* w)
{
	if (mRenderTex != nullptr)
	{
		//��ȡ��Ϸ����ռ���Ϣ
		auto trans = mGameObject->mTransform;

		//����������Ⱦ�ӿڣ����Ƶ�������
		Vector2 leftTopPos = trans->GetPosition() -
			mRenderTex->GetSize() * trans->GetScale() / 2;

		w->CopyTextureToRenderer(mRenderTex,
			leftTopPos,
			trans->GetRotation(),
			trans->GetScale(),
			&mRenderTex->rectRgn,		//�ü�����
			{ 0, 0 },	//ƫ��
			false, false);	//X��Y�������Ƿ�ת

		// ���ư�Χ��
		w->SetPenColor(255, 255, 0, 255);
		w->DrawRectangle(GetBounds());
	}
}
