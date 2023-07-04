#include "ImageManagement.h"
#include <iostream>
#include <filesystem>

SDL_Texture* ImageManagement::LoadImageByPath(std::string path)
{
    //��·������ͼƬΪ�����ļ�
    //ע�⣺�����ȡ���ı����ļ��ǿյģ�����û���κα���������zlib1.dll�ļ�û�з��ڸ�Ŀ¼��
    //����ͼƬ��Ҫ��dll�ļ���SDL2_image.dll��zlib1.dll������������������Ҫ����ͼƬ��ʽ��libjpeg-9.dll��libpng16-16.dll
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface)
    {
        SDL_Log(u8"�򿪴�ͼƬʧ�ܣ�%s", path.c_str());
        return nullptr;
    }

    //�����ļ�תΪ����
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);   //�����ļ��ǳ��Ŀռ䣬���������ͷ�
    if (!texture)
    {
        SDL_Log(u8"�����ļ�ת����ʧ�ܣ�%s", path.c_str());
        return nullptr;
    }
    return texture;
}

ImageManagement::ImageManagement(SDL_Renderer* renderer, std::string parentPath)
    : mRenderer(renderer), mParentPath(parentPath)
{
}

ImageManagement::~ImageManagement()
{
    ////���������ͷ����������г�Ա������ڴ�
    //for (auto it = mTextureRegister.begin(); it != mTextureRegister.end(); it++)
    //{
    //    SDL_DestroyTexture((*it).second);
    //}
    ////ͨ�����������������ʱ������������ռ�ÿռ��ں����������Զ����٣�
    //decltype(mTextureRegister) emptyMap;
    //mTextureRegister.swap(emptyMap);     //ֻʣ��0Ԫ��0��С������
}

SDL_Texture* ImageManagement::GetSDLTextureByFullPath(std::string path)
{
    // ���ַ����Ͳ�Ҫ������ͼƬ����û����ʲô��
    if (path.empty())
        return nullptr;

    ////������������Ѱ������
    //SDL_Texture* texture = nullptr;
    //auto it = mTextureRegister.find(path);

    ////���û���������ҵ������ļ��м���ͼƬ
    //if (it == mTextureRegister.end())
    //{
    //    //SDL_Log(u8"����ͼƬ��·����%s", path.c_str());
    //    texture = LoadImageByPath(path);

    //    if (texture)
    //        mTextureRegister[path] = texture;    //�ҵ�ͼƬ����ӵ�����
    //    else;
    //        //SDL_Log(u8"����ͼƬʧ�ܣ�·����%s", path.c_str());
    //}

    //else
    //    texture = (*it).second;

    //return texture;
    return LoadImageByPath(path);
}

Texture* ImageManagement::SDLTextureToTexture(SDL_Texture* sdlTexture)  const
{
    if (sdlTexture == nullptr)
        return nullptr;

    //��ȡ�����С���ü���ϢΪ���ü���ԭͼ��
    Math::rectangle_i rectRgn{0, 0, 0, 0};
    Uint32 pixelFormat;
    int access;
    SDL_QueryTexture(sdlTexture, &pixelFormat, &access, &rectRgn.w, &rectRgn.h);
    //�����������
    return new Texture(sdlTexture, rectRgn);
}

Texture* ImageManagement::GetTextureByFullPath(std::string path)
{
    //ͨ��·����ȡsdl����
    SDL_Texture* sdlTexture = GetSDLTextureByFullPath(path);
    if (sdlTexture == nullptr)
        return nullptr;

    // ��sdl����ת����ͨ������
    Texture* texture = SDLTextureToTexture(sdlTexture);

    // ֱ�ӷ���������������
    return texture;
}

Texture* ImageManagement::GetTextureByPath(std::string name)
{
    return GetTextureByFullPath(mParentPath + name);
}

std::vector<Texture*> ImageManagement::GetTexturesByDir(std::string dir)
{
    std::vector<Texture*> textures;

    std::string dir_path = mParentPath + dir;
    std::string suffix = ".png";

    try {
        // �ļ�������
        for (auto& entry : std::filesystem::directory_iterator(dir_path)) 
        {
            //����Ƿ�Ϊ�����ļ��������ļ���׺
            if (entry.is_regular_file() && entry.path().extension() == suffix) 
            {
                //std::cout << entry.path().filename() << std::endl;
                textures.emplace_back( 
                    GetTextureByFullPath(dir_path + '/' + entry.path().filename().string()) 
                );
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return textures;
}

Texture* ImageManagement::CopyTexture(const Texture* myTex) const
{
    if (myTex == nullptr || myTex->sdlTexture == nullptr)
        return nullptr;

    SDL_Texture* srcTex = myTex->sdlTexture;

    // ��ȡ�����С
    int width, height;
    Uint32 format;
    int access;
    SDL_QueryTexture(srcTex, &format, &access, &width, &height);

    // �����м����
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, format);

    SDL_Rect rect{ 0, 0, width, height };
    // ����ȾĿ�������Ƶ�������
    SDL_Texture* tempTex = SDL_CreateTexture(mRenderer, format, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(srcTex, SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(mRenderer, tempTex);
    SDL_RenderCopy(mRenderer, srcTex, &rect, &rect);

    // �������ȡ�������ݵ��м������
    SDL_RenderReadPixels(mRenderer, &rect, surface->format->format, surface->pixels, surface->pitch);

    SDL_SetRenderTarget(mRenderer, NULL);
    SDL_SetTextureBlendMode(srcTex, SDL_BLENDMODE_BLEND);

    // ������ת��������
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

    // �����м����
    SDL_DestroyTexture(tempTex);
    SDL_FreeSurface(surface);

    // ����������
    return SDLTextureToTexture(newTexture);
}

std::vector<Texture*> ImageManagement::CopyTextures(const std::vector<Texture*>& srcTextures)
{
    std::vector<Texture*> dstTextures;
    for (auto tex : srcTextures)
    {
        dstTextures.emplace_back(CopyTexture(tex));
    }
    return dstTextures;
}

std::vector<Texture*> ImageManagement::SplitTexture(Texture* sourceTexture, uint16_t x, uint16_t y)
{
    std::vector<Texture*> textures;
    // ������ƬС��ĳߴ�
    Vector2 size(sourceTexture->GetSize() /= Vector2(x, y));
    Math::rectangle_i rect = { 0, 0, size.x, size.y };

    for (uint16_t i = 0; i < y; i++)
    {
        for (uint16_t j = 0; j < x; j++)
        {
            // ����ͬһ��sdlTexture�����ǲü�����ͬ
            Texture* newTex = new Texture(sourceTexture->sdlTexture, rect);
            textures.emplace_back(newTex);
            // ������һ�ŵĲü��������ƣ�
            rect.x += size.x;
        }
        // ����
        rect.x = 0;
        rect.y += size.y;
    }

    return textures;
}


