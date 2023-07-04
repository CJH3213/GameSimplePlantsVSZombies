#include "GraveButton.h"
#include "GameObject.h"

GraveButton::GraveButton(std::string normalPath, std::string highLigPath)
	: ImageButton(normalPath, highLigPath, "")
{
}

void GraveButton::Awake()
{
	//��ִ�и������ʼ��
	ImageButton::Awake();

	// ��ײ�����õñ�ͼƬСЩ
	mSize -= Vector2(20, 60);

	// ע�ᰴť�����¼�
	mMouseDownEvents.AddListener("GraveBtnDown", std::bind(&GraveButton::OnMouseDown, this));
	// ע�ᰴţ̌���¼�
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
