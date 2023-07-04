#include "TextButton.h"
#include "Game.h"

TextButton::TextButton(std::wstring text,
	FontStyle normalSty, FontStyle highLigSty)
	: ImageButton("", "", ""), mContent(text),
	mNormalStyle(normalSty), mHighLigStyle(highLigSty)
{
}

void TextButton::Awake()
{
	ImageButton::Awake();

	// �ı���������
	auto game = GetGame();
	mNormalTex = game->mFontManager->TextToTexture(mContent, mNormalStyle);
	mHighLigTex = game->mFontManager->TextToTexture(mContent, mHighLigStyle);
	mRenderTex = mNormalTex;
}
