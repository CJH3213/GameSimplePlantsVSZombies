#include "Script02.h"
#include "Game.h"
#include "AdventurePage.h"

void Script02::Awake()
{
	mBtnStart->OnClick.AddListener("Script02Start",
		[this]() {
			// 点击开始冒险，进入对战界面
			GetGame()->mSceneManager->LoadScene(
				new AdventurePage("AdventurePage_Level01")
			);
		});

	mBtnExit->OnClick.AddListener( "Script02Exit",
		[this]() {
			// 按钮点击，结束游戏
			GetGame()->QuitGame();
		});
}
