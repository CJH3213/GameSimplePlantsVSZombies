#include "PrefabManager.h"

PrefabManager::PrefabManager(Game* game) :
	mGame(game), mVirtualScene("VirtualScene")
{
	mVirtualScene.mGame = mGame;
}
