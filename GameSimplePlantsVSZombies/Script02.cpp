#include "Script02.h"
#include "Game.h"
#include "AdventurePage.h"

void Script02::Awake()
{
	mBtnStart->OnClick.AddListener("Script02Start",
		[this]() {
			// �����ʼð�գ������ս����
			GetGame()->mSceneManager->LoadScene(
				new AdventurePage("AdventurePage_Level01")
			);
		});

	mBtnExit->OnClick.AddListener( "Script02Exit",
		[this]() {
			// ��ť�����������Ϸ
			GetGame()->QuitGame();
		});
}
