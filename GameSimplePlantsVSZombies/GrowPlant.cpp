#include "GrowPlant.h"
#include "TextureRender.h"
#include "GrowPlantScript.h"
#include "Button.h"

void GrowPlant::Instantiate()
{
	// ���ֲ��ʾ��ͼ
	TextureRender* imgC = new TextureRender(nullptr, 4);
	AddComponent(imgC);
	// ��ӿ��ƽű�
	GrowPlantScript* script = new GrowPlantScript();
	AddComponent(script);
}
