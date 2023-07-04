#include "Button.h"
#include "Game.h"
#include "Input.h"
#include "TransformComponent.h"

void Button::Awake()
{
	// ����Ⱦ�����ӵ���Ⱦ������
	GetGame()->mRenderManager->AddComponent(this);
	// �������ײ�����ӵ���ײ������
	GetGame()->mCollisionManager->AddPointer(this);
}

Button::~Button()
{
	// ����ǰ�������Ⱦ����������
	GetGame()->mRenderManager->RemoveComponent(this);
	// ����ǰ�������ײ����������
	GetGame()->mCollisionManager->RemovePointer(this);
}

ComponentBase* Button::Clone() const
{
	Button* newComp = new Button();

	// ��Ҫ�������״̬��ʵʱ���㼴��

	//������ײ������
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
	// �����Ծ������²Ž�������¼�
	if (mIsEnable)
	{
		// ��¼�����ͣ����ײ����
		mMouseHover[1] = true;
		// ��¼�������ײ����ֻҪ�������
		if (Input::GetMouseButton(0))
		{
			mMouseClick[1] = true;
		}
	}
}

void Button::LateMouseUpdate(Vector2 )
{
	// �����ͣ�¼�
	if (mMouseHover[0] == false)
	{
		if (mMouseHover[1] == true)
		{
			//��һ֡������
			mMouseEnterEvents.InvokeAll();
		}
	}
	else
	{
		if (mMouseHover[1] == true)
		{
			//��������ͣ
			mMouseOverEvents.InvokeAll();;
		}
		else
		{
			//����뿪
			mMouseExitEvents.InvokeAll();
		}
	}
	// �����μ�¼ֵ��Ϊ�ϼ�¼��Ϊ�´���׼��
	mMouseHover[0] = mMouseHover[1];
	mMouseHover[1] = false;

	// ������¼�
	if (mMouseClick[0] == false)
	{
		if (mMouseClick[1] == true)
		{
			//��һ֡����������
			mMouseDownEvents.InvokeAll();
		}
	}
	else
	{
		// ��¼�������ײ����ֻҪ�������
		if (Input::GetMouseButton(0))
			mMouseClick[1] = true;

		if (mMouseClick[1] == true)
		{
			//��������������
			mMouseDragEvents.InvokeAll();
		}
		else
		{
			//�������ͷ�
			mMouseUpEvents.InvokeAll();

			// �������ɿ�ʱ����Ȼ��ͣ����ײ���ϣ����ö�Ӧ�ص�
			if (mMouseHover[0])
			{
				mMouseUpAsButtonEvents.InvokeAll();
			}
		}
	}
	// �����μ�¼ֵ��Ϊ�ϼ�¼��Ϊ�´���׼��
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
	// ���ư�Χ��
	w->SetPenColor(255, 0, 0, 255);
	w->DrawRectangle(GetBounds());
}
