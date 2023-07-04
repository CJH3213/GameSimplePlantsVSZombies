#pragma once
#include <string>
#include <SDL_image.h>
#include "Texture.h"
#include <unordered_map>
#include <vector>

class ImageManagement
{
private:
	// �ݴ�����
	//std::unordered_map<std::string, SDL_Texture*> mTextureRegister;
	// ��Ⱦ��
	SDL_Renderer* mRenderer;
	// ͼƬ��Դ��·���������ļ��е����ͼƬ���ļ��е����·�����磺"Resource/Images/"
	std::string mParentPath;

	// ͨ���ļ�·������ͼƬ����ת��Ϊ����
	SDL_Texture* LoadImageByPath(std::string path);
	// ͨ��·����ȡ����
	SDL_Texture* GetSDLTextureByFullPath(std::string path);
	// ��SDLTextureת��ΪTexture
	Texture* SDLTextureToTexture(SDL_Texture* sdlTexture)  const;

	Texture* GetTextureByFullPath(std::string path);

public:
	ImageManagement(SDL_Renderer* renderer, std::string parentPath);
	~ImageManagement();

	// ͨ��ͼƬ����ȡ����·����ͼƬ����
	Texture* GetTextureByPath(std::string name);
	// ����һ�������ļ��У�
	std::vector<Texture*> GetTexturesByDir(std::string dir);
	// ��������
	Texture* CopyTexture(const Texture* texture) const;
	// ������������
	std::vector<Texture*> CopyTextures(const std::vector<Texture*>& srcTextures);
	// �ָ�����
	std::vector<Texture*> SplitTexture(Texture* sourceTexture, uint16_t x, uint16_t y);
};

