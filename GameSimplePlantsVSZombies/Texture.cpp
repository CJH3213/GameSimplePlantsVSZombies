#include "Texture.h"

Texture::Texture(SDL_Texture* texture)
{
	this->sdlTexture = texture;
	// �Զ���ȡ�����С
	SDL_QueryTexture(texture, nullptr, nullptr, &rectRgn.w, &rectRgn.h);
}

Texture::Texture(SDL_Texture* sdlTexture, int x, int y, int w, int h)
{
	this->sdlTexture = sdlTexture;
	rectRgn = {x, y, w, h};
}

Texture::Texture(SDL_Texture* sdlTexture, const Math::rectangle_i& rgn)
{
	this->sdlTexture = sdlTexture;
	rectRgn = rgn;
}

Texture::Texture(SDL_Texture* texture, const Vector2& size):
	Texture(texture, 0, 0, (int)size.x, (int)size.y)
{
}

Texture::~Texture()
{
	SDL_DestroyTexture(sdlTexture);
	sdlTexture = nullptr;
}

void Texture::SetRectRgn(const Math::rectangle_i& rgn)
{
	
	rectRgn = rgn;
}

void Texture::SetTextureAlpha(uint8_t alpha)
{
	mAlpha = alpha;
	// �ı�����͸����ֻ��Ҫ����һ�μ��ɣ������һֱ����͸����
	//SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(sdlTexture, mAlpha);
}
