#include "FontManager.h"

TTF_Font* FontManager::LoadFont(std::string path, size_t ptsize)
{
    // 查找是否已经加载过该字体
    std::string key = path + std::to_string(ptsize);
    auto iter = mFontRegister.find(key);
    // 如果找不到，加载字库
    if (iter == mFontRegister.end())
    {
        TTF_Font* font = TTF_OpenFont(path.c_str(), ptsize);
        if (font != nullptr)
        {
            mFontRegister.insert({ key, font });
            return font;
        }
        else
            return nullptr;
    }
    else
        return (*iter).second;
}

FontManager::FontManager(SDL_Renderer* renderer, std::string parentPath)
    : mRenderer(renderer), mParentPath(parentPath) 
{
    //初始化TTF库
    if (TTF_Init() == -1)
    {
        SDL_Log(u8"TTF_Init错误，错误信息：%s", TTF_GetError());
    }
}

FontManager::~FontManager()
{
    // 卸载字库
    for (auto& font : mFontRegister)
        TTF_CloseFont(font.second);
    //通过与空容器交换，临时容器带着容器占用空间在函数结束后自动销毁，
   decltype(mFontRegister) emptyMap;
    mFontRegister.swap(emptyMap);     //只剩下0元素0大小的容器

    TTF_Quit();
}

Texture* FontManager::TextToTexture(std::wstring str, FontStyle style)
{
    // 设置TTF字体效果
    TTF_Font* font = LoadFont(mParentPath + style.fontName + ".ttf", style.size);
    TTF_SetFontStyle(font, style.glyph);
    // 创建文本表面
    SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(font, 
        (Uint16*)str.c_str(), style.color.GetSDLColor());
    // 转换贴图为纹理
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    // 释放表面资源
    SDL_FreeSurface(textSurface);

    return new Texture(textTexture);
}
;