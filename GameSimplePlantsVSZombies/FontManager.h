#pragma once
#include <unordered_map>
#include <string>
#include <SDL_ttf.h>
#include "Color.h"
#include "Texture.h"

// 字形（可以逻辑或同时实现多种样式）
enum FontGlyph
{
	Normal = 0x00,	//正常
	Bold = 0x01,		//粗体
	Italic = 0x02,		//斜体
	UnderLine = 0x04,	//下划线
	StrikeThrough = 0x08		//删除线
};

// 字体样式
struct FontStyle
{
	std::string fontName = "simhei";	//字库名称
	size_t size = 12;	//字体大小
	Color color = {255, 0, 0, 0};	//字体颜色
	FontGlyph glyph = FontGlyph::Normal;
};

class FontManager
{
private:
	//暂存字体
	std::unordered_map<std::string, TTF_Font*> mFontRegister;
	//渲染器
	SDL_Renderer* mRenderer;
	//图片资源父路径，程序文件夹到存放字体的文件夹的相对路径，如："Resource/Fonts/"
	std::string mParentPath;

	//通过字库路径和字体大小加载字库
	TTF_Font* LoadFont(std::string path, size_t ptsize);

public:
	// 构造函数
	FontManager(SDL_Renderer* renderer, std::string parentPath);
	// 析构函数
	~FontManager();

	// 将字符串生成纹理
	Texture* TextToTexture(std::wstring str, FontStyle style);
};

