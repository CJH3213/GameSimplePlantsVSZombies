#include "ImageManagement.h"
#include <iostream>
#include <filesystem>

SDL_Texture* ImageManagement::LoadImageByPath(std::string path)
{
    //从路径加载图片为表面文件
    //注意：如果获取到的表面文件是空的，并且没有任何报错，可能是zlib1.dll文件没有放在根目录，
    //加载图片需要的dll文件：SDL2_image.dll、zlib1.dll、（下面两个看你需要那种图片格式）libjpeg-9.dll、libpng16-16.dll
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface)
    {
        SDL_Log(u8"打开此图片失败：%s", path.c_str());
        return nullptr;
    }

    //表面文件转为纹理
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);   //表面文件非常耗空间，用完马上释放
    if (!texture)
    {
        SDL_Log(u8"表面文件转纹理失败：%s", path.c_str());
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
    ////析构，先释放容器内所有成员本体的内存
    //for (auto it = mTextureRegister.begin(); it != mTextureRegister.end(); it++)
    //{
    //    SDL_DestroyTexture((*it).second);
    //}
    ////通过与空容器交换，临时容器带着容器占用空间在函数结束后自动销毁，
    //decltype(mTextureRegister) emptyMap;
    //mTextureRegister.swap(emptyMap);     //只剩下0元素0大小的容器
}

SDL_Texture* ImageManagement::GetSDLTextureByFullPath(std::string path)
{
    // 空字符串就不要找啦，图片名都没有拿什么找
    if (path.empty())
        return nullptr;

    ////尝试在容器中寻找纹理
    //SDL_Texture* texture = nullptr;
    //auto it = mTextureRegister.find(path);

    ////如果没在容器中找到，从文件夹加载图片
    //if (it == mTextureRegister.end())
    //{
    //    //SDL_Log(u8"加载图片，路径：%s", path.c_str());
    //    texture = LoadImageByPath(path);

    //    if (texture)
    //        mTextureRegister[path] = texture;    //找到图片就添加到容器
    //    else;
    //        //SDL_Log(u8"加载图片失败，路径：%s", path.c_str());
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

    //获取纹理大小（裁剪信息为不裁剪，原图）
    Math::rectangle_i rectRgn{0, 0, 0, 0};
    Uint32 pixelFormat;
    int access;
    SDL_QueryTexture(sdlTexture, &pixelFormat, &access, &rectRgn.w, &rectRgn.h);
    //创建纹理对象
    return new Texture(sdlTexture, rectRgn);
}

Texture* ImageManagement::GetTextureByFullPath(std::string path)
{
    //通过路径获取sdl纹理
    SDL_Texture* sdlTexture = GetSDLTextureByFullPath(path);
    if (sdlTexture == nullptr)
        return nullptr;

    // 将sdl纹理转换成通用纹理
    Texture* texture = SDLTextureToTexture(sdlTexture);

    // 直接返回纹理，不拷贝了
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
        // 文件迭代器
        for (auto& entry : std::filesystem::directory_iterator(dir_path)) 
        {
            //检查是否为常规文件，检验文件后缀
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

    // 获取纹理大小
    int width, height;
    Uint32 format;
    int access;
    SDL_QueryTexture(srcTex, &format, &access, &width, &height);

    // 创建中间表面
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, format);

    SDL_Rect rect{ 0, 0, width, height };
    // 将渲染目标纹理复制到表面中
    SDL_Texture* tempTex = SDL_CreateTexture(mRenderer, format, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(srcTex, SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(mRenderer, tempTex);
    SDL_RenderCopy(mRenderer, srcTex, &rect, &rect);

    // 从纹理读取像素数据到中间表面上
    SDL_RenderReadPixels(mRenderer, &rect, surface->format->format, surface->pixels, surface->pitch);

    SDL_SetRenderTarget(mRenderer, NULL);
    SDL_SetTextureBlendMode(srcTex, SDL_BLENDMODE_BLEND);

    // 将表面转换回纹理
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

    // 销毁中间表面
    SDL_DestroyTexture(tempTex);
    SDL_FreeSurface(surface);

    // 返回新纹理
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
    // 计算切片小块的尺寸
    Vector2 size(sourceTexture->GetSize() /= Vector2(x, y));
    Math::rectangle_i rect = { 0, 0, size.x, size.y };

    for (uint16_t i = 0; i < y; i++)
    {
        for (uint16_t j = 0; j < x; j++)
        {
            // 公用同一个sdlTexture，但是裁剪区域不同
            Texture* newTex = new Texture(sourceTexture->sdlTexture, rect);
            textures.emplace_back(newTex);
            // 计算下一张的裁剪区域（右移）
            rect.x += size.x;
        }
        // 换行
        rect.x = 0;
        rect.y += size.y;
    }

    return textures;
}


