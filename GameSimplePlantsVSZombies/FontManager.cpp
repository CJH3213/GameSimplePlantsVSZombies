#include "FontManager.h"

TTF_Font* FontManager::LoadFont(std::string path, size_t ptsize)
{
    // �����Ƿ��Ѿ����ع�������
    std::string key = path + std::to_string(ptsize);
    auto iter = mFontRegister.find(key);
    // ����Ҳ����������ֿ�
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
    //��ʼ��TTF��
    if (TTF_Init() == -1)
    {
        SDL_Log(u8"TTF_Init���󣬴�����Ϣ��%s", TTF_GetError());
    }
}

FontManager::~FontManager()
{
    // ж���ֿ�
    for (auto& font : mFontRegister)
        TTF_CloseFont(font.second);
    //ͨ�����������������ʱ������������ռ�ÿռ��ں����������Զ����٣�
   decltype(mFontRegister) emptyMap;
    mFontRegister.swap(emptyMap);     //ֻʣ��0Ԫ��0��С������

    TTF_Quit();
}

Texture* FontManager::TextToTexture(std::wstring str, FontStyle style)
{
    // ����TTF����Ч��
    TTF_Font* font = LoadFont(mParentPath + style.fontName + ".ttf", style.size);
    TTF_SetFontStyle(font, style.glyph);
    // �����ı�����
    SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(font, 
        (Uint16*)str.c_str(), style.color.GetSDLColor());
    // ת����ͼΪ����
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    // �ͷű�����Դ
    SDL_FreeSurface(textSurface);

    return new Texture(textTexture);
}
;