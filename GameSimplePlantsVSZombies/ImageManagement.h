#pragma once
#include <string>
#include <SDL_image.h>
#include "Texture.h"
#include <unordered_map>
#include <vector>

class ImageManagement
{
private:
	// 暂存纹理
	//std::unordered_map<std::string, SDL_Texture*> mTextureRegister;
	// 渲染器
	SDL_Renderer* mRenderer;
	// 图片资源父路径，程序文件夹到存放图片的文件夹的相对路径，如："Resource/Images/"
	std::string mParentPath;

	// 通过文件路径加载图片，并转换为纹理
	SDL_Texture* LoadImageByPath(std::string path);
	// 通过路径获取纹理
	SDL_Texture* GetSDLTextureByFullPath(std::string path);
	// 将SDLTexture转换为Texture
	Texture* SDLTextureToTexture(SDL_Texture* sdlTexture)  const;

	Texture* GetTextureByFullPath(std::string path);

public:
	ImageManagement(SDL_Renderer* renderer, std::string parentPath);
	~ImageManagement();

	// 通过图片名获取纹理（路径：图片名）
	Texture* GetTextureByPath(std::string name);
	// 加载一组纹理（文件夹）
	std::vector<Texture*> GetTexturesByDir(std::string dir);
	// 拷贝纹理
	Texture* CopyTexture(const Texture* texture) const;
	// 拷贝多张纹理
	std::vector<Texture*> CopyTextures(const std::vector<Texture*>& srcTextures);
	// 分割纹理
	std::vector<Texture*> SplitTexture(Texture* sourceTexture, uint16_t x, uint16_t y);
};

