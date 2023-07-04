#include "TextComponent.h"
#include "Game.h"

TextComponent::TextComponent(
	std::wstring text, const FontStyle& style)
	: TextureRender(nullptr), mContent(text), mStyle(style)
{
}

TextComponent::~TextComponent()
{
	// ����ǰ�������Ⱦ�������
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
	// ���θ����ı���������
	Regenerate();
	//����Ⱦ�����ӵ���Ⱦ������
	GetGame()->mRenderManager->AddComponent(this);
}

void TextComponent::SetContent(std::wstring str)
{
	mContent = str;
	// ��������������������
	Regenerate();
}

void TextComponent::SetStyle(FontStyle& style)
{
	mStyle = style;
	// ��������ʽ������������
	Regenerate();
}

void TextComponent::Set(std::wstring str, FontStyle& style)
{
	mContent = str;
	mStyle = style;
	// ��������ʽ������������
	Regenerate();
}

void TextComponent::Regenerate()
{
	auto* game = GetGame();
	if(game)
		mTexture = game->mFontManager->TextToTexture(mContent, mStyle);
}
