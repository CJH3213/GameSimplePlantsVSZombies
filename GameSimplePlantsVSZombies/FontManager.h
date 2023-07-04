#pragma once
#include <unordered_map>
#include <string>
#include <SDL_ttf.h>
#include "Color.h"
#include "Texture.h"

// ���Σ������߼���ͬʱʵ�ֶ�����ʽ��
enum FontGlyph
{
	Normal = 0x00,	//����
	Bold = 0x01,		//����
	Italic = 0x02,		//б��
	UnderLine = 0x04,	//�»���
	StrikeThrough = 0x08		//ɾ����
};

// ������ʽ
struct FontStyle
{
	std::string fontName = "simhei";	//�ֿ�����
	size_t size = 12;	//�����С
	Color color = {255, 0, 0, 0};	//������ɫ
	FontGlyph glyph = FontGlyph::Normal;
};

class FontManager
{
private:
	//�ݴ�����
	std::unordered_map<std::string, TTF_Font*> mFontRegister;
	//��Ⱦ��
	SDL_Renderer* mRenderer;
	//ͼƬ��Դ��·���������ļ��е����������ļ��е����·�����磺"Resource/Fonts/"
	std::string mParentPath;

	//ͨ���ֿ�·���������С�����ֿ�
	TTF_Font* LoadFont(std::string path, size_t ptsize);

public:
	// ���캯��
	FontManager(SDL_Renderer* renderer, std::string parentPath);
	// ��������
	~FontManager();

	// ���ַ�����������
	Texture* TextToTexture(std::wstring str, FontStyle style);
};

