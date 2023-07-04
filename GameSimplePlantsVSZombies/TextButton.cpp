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

	// 文本生成纹理
	auto game = GetGame();
	mNormalTex = game->mFontManager->TextToTexture(mContent, mNormalStyle);
	mHighLigTex = game->mFontManager->TextToTexture(mContent, mHighLigStyle);
	mRenderTex = mNormalTex;
}
