#include "ProgressGameObject.h"

ProgressGameObject::ProgressGameObject(string name, GameObject* go, int drawOrder):
	GameObject(name, go, drawOrder)
{
}

ProgressGameObject::~ProgressGameObject()
{
}

void ProgressGameObject::SetProgress(float f)
{
	if (f > 1.0)
		f = 1.0;
	progress = f;

	//���ݽ������ý������ü���Χ
	Vector2 barFullSize = barRenderer->GetFullSize();
	Vector2 barRgnSize = Vector2(barFullSize.x * progress, barFullSize.y);
	barRenderer->SetRegionRect(MathBase::rectangle_i{ 0, 0, 
		static_cast<int>(barRgnSize.x), static_cast<int>(barRgnSize.y) });

	//���ݽ������ý��ȵ�λ�ú���ת�Ƕ�
	//pointSprite->transform->GetAbsolutePosition() = Vector2(barFullSize.x / 2 + barRgnSize.x, 0);
	//pointSprite->transform-> = 360 * progress;
}

void ProgressGameObject::SetBackGroundSprite(SpriteGameObject* sgo)
{
	backgroundSprite = sgo;
	AddGameObject(backgroundSprite);
}

void ProgressGameObject::SetBarSprite(SpriteGameObject* sgo)
{
	barSprite = sgo;
	AddGameObject(barSprite);

	//��ȡ����������Ⱦ���
	barRenderer = (RendererComponent*)barSprite->GetComponent<RendererComponent>();
}

void ProgressGameObject::SetPointSprite(SpriteGameObject* sgo)
{
	pointSprite = sgo;
	AddGameObject(pointSprite);
}
