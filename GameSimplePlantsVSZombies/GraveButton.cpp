#include "GraveButton.h"
#include "GameObject.h"

GraveButton::GraveButton(std::string normalPath, std::string highLigPath)
	: ImageButton(normalPath, highLigPath, "")
{
}

void GraveButton::Awake()
{
	//先执行父组件初始化
	ImageButton::Awake();

	// 碰撞框设置得比图片小些
	mSize -= Vector2(20, 60);

	// 注册按钮按下事件
	mMouseDownEvents.AddListener("GraveBtnDown", std::bind(&GraveButton::OnMouseDown, this));
	// 注册按钮抬起事件
	mMouseDownEvents.AddListener("GraveBtnUp", std::bind(&GraveButton::OnMouseUp, this));
}

void GraveButton::OnMouseDown()
{
	mOffset = { 4, 4 };
}

void GraveButton::OnMouseUp()
{
	mOffset = { 0, 0 };
}
