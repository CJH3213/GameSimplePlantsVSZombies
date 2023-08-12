#include "FlagMeterScript.h"
#include "SliderComponent.h"
#include "GameObject.h"
#include "TextureRender.h"
#include "Game.h"

void FlagMeterScript::SetProgress(float value)
{
	mSlider->SetValue(value);
}

void FlagMeterScript::AddFlag(float percent)
{
	// 计算旗帜位置
	int w = percent * mFillSize.x;
	int x = mFillSize.x / 2 - w;
	int y = mFill->mTransform->localPosition.y - mFillSize.y/2;

	// 纹理渲染组件：旗子
	GameObject* flagObj = new GameObject("");
	GetScene()->AddGameObject(flagObj);
	flagObj->SetParent(mGameObject);
	flagObj->mTransform->localPosition = Vector2(x, y);

	Texture* flagTexture = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/FlagMeterParts.png");
	flagTexture->SetRectRgn({ 50, 0, 25, 25 });

	TextureRender* flagRender = new TextureRender(flagTexture, mDrawOrder);
	flagObj->AddComponent(flagRender);
	flagRender->mOffset.x = 10;	//把旗杆棍对准进度
}

void FlagMeterScript::Awake()
{
	auto fillRender = mFill->GetComponent<TextureRender>();
	auto fillRect = fillRender->mTexture->rectRgn;
	mFillSize = Vector2(fillRect.w, fillRect.h );
	mDrawOrder = fillRender->GetDrawOrder();
}
