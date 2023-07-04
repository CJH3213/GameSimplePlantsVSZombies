#include "Turf.h"
#include "Button.h"
// #include "BoxCollider.h"
#include "TurfScript.h"

void Turf::Instantiate()
{
	Vector2 turfSize = { 80, 100 };

	mTag = "Turf";
	//mName = "TurfCollider_" + std::to_string(index);

	// 添加点击组件
	Button* button = new Button();
	AddComponent(button);
	button->mSize = turfSize;

	// 添加碰撞器组件
	//BoxCollider* collider = new BoxCollider();
	//AddComponent(collider);
	//collider->SetEnable(false);
	//collider->mSize = { 60, 70 };

	// 添加脚本
	TurfScript* script = new TurfScript();
	AddComponent(script);
	script->mBtn = button;
}
