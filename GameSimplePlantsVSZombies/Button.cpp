#include "Button.h"
#include "Game.h"
#include "Input.h"
#include "TransformComponent.h"

void Button::Awake()
{
	// 将渲染组件添加到渲染管理器
	GetGame()->mRenderManager->AddComponent(this);
	// 将鼠标碰撞组件添加到碰撞管理器
	GetGame()->mCollisionManager->AddPointer(this);
}

Button::~Button()
{
	// 将当前组件与渲染管理器分离
	GetGame()->mRenderManager->RemoveComponent(this);
	// 将当前组件与碰撞管理器分离
	GetGame()->mCollisionManager->RemovePointer(this);
}

ComponentBase* Button::Clone() const
{
	Button* newComp = new Button();

	// 不要复制鼠标状态，实时运算即可

	//复制碰撞盒属性
	newComp->mSize = mSize;
	newComp->mOffset = mOffset;

	return newComp;
}

Rectangle Button::GetBounds()
{
	return Rectangle(GetTransform()->GetPosition() + mOffset, mSize);
}

void Button::OnMouseCallback(Vector2 pos)
{
	// 组件活跃的情况下才接收鼠标事件
	if (mIsEnable)
	{
		// 记录鼠标悬停于碰撞器上
		mMouseHover[1] = true;
		// 记录鼠标点击碰撞器，只要左键按下
		if (Input::GetMouseButton(0))
		{
			mMouseClick[1] = true;
		}
	}
}

void Button::LateMouseUpdate(Vector2 )
{
	// 鼠标悬停事件
	if (mMouseHover[0] == false)
	{
		if (mMouseHover[1] == true)
		{
			//这一帧鼠标进入
			mMouseEnterEvents.InvokeAll();
		}
	}
	else
	{
		if (mMouseHover[1] == true)
		{
			//鼠标持续悬停
			mMouseOverEvents.InvokeAll();;
		}
		else
		{
			//鼠标离开
			mMouseExitEvents.InvokeAll();
		}
	}
	// 将本次记录值作为老记录，为下次作准备
	mMouseHover[0] = mMouseHover[1];
	mMouseHover[1] = false;

	// 鼠标点击事件
	if (mMouseClick[0] == false)
	{
		if (mMouseClick[1] == true)
		{
			//这一帧鼠标左键按下
			mMouseDownEvents.InvokeAll();
		}
	}
	else
	{
		// 记录鼠标点击碰撞器，只要左键按下
		if (Input::GetMouseButton(0))
			mMouseClick[1] = true;

		if (mMouseClick[1] == true)
		{
			//鼠标左键持续按下
			mMouseDragEvents.InvokeAll();
		}
		else
		{
			//鼠标左键释放
			mMouseUpEvents.InvokeAll();

			// 鼠标左键松开时，仍然悬停在碰撞器上，调用对应回调
			if (mMouseHover[0])
			{
				mMouseUpAsButtonEvents.InvokeAll();
			}
		}
	}
	// 将本次记录值作为老记录，为下次作准备
	mMouseClick[0] = mMouseClick[1];
	mMouseClick[1] = false;
}

GameObject* Button::GetGameObj()
{
	return mGameObject;
}

bool Button::IsIntersectWithPoint(const Vector2& pos)
{
	
	return GetBounds().IsIntersect(pos);
}

void Button::OnRender(Window* w)
{
	// 绘制包围盒
	w->SetPenColor(255, 0, 0, 255);
	w->DrawRectangle(GetBounds());
}
