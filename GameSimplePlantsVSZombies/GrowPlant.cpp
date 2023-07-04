#include "GrowPlant.h"
#include "TextureRender.h"
#include "GrowPlantScript.h"
#include "Button.h"

void GrowPlant::Instantiate()
{
	// 添加植物示意图
	TextureRender* imgC = new TextureRender(nullptr, 4);
	AddComponent(imgC);
	// 添加控制脚本
	GrowPlantScript* script = new GrowPlantScript();
	AddComponent(script);
}
