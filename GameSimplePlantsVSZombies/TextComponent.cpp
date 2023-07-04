#include "TextComponent.h"
#include "Game.h"

TextComponent::TextComponent(
	std::wstring text, const FontStyle& style)
	: TextureRender(nullptr), mContent(text), mStyle(style)
{
}

TextComponent::~TextComponent()
{
	// 将当前组件与渲染组件分离
	GetGame()->mRenderManager->RemoveComponent(this);
}

ComponentBase* TextComponent::Clone() const
{
	TextComponent* newComp = 
		new TextComponent(mContent, mStyle);

	return newComp;
}

void TextComponent::Awake()
{
	// 初次根据文本生成纹理
	Regenerate();
	//将渲染组件添加到渲染管理器
	GetGame()->mRenderManager->AddComponent(this);
}

void TextComponent::SetContent(std::wstring str)
{
	mContent = str;
	// 根据内容重新生成纹理
	Regenerate();
}

void TextComponent::SetStyle(FontStyle& style)
{
	mStyle = style;
	// 根据新样式重新生成纹理
	Regenerate();
}

void TextComponent::Set(std::wstring str, FontStyle& style)
{
	mContent = str;
	mStyle = style;
	// 根据新样式重新生成纹理
	Regenerate();
}

void TextComponent::Regenerate()
{
	auto* game = GetGame();
	if(game)
		mTexture = game->mFontManager->TextToTexture(mContent, mStyle);
}
