#pragma once
#include <SDL.h>
#include "MathBase.h"
#include "Vector2.h"

/// <summary>
/// ��SDL��Texture���ͽ��г���
/// ���ʹ������ͼ�ο⣬������ʵ�ֶ�Ӧ����
/// </summary>
class Texture
{
private:
	// ͸��ͨ����Ĭ�ϲ�͸����
	uint8_t mAlpha = 0xFF;

public:
	//ԭ����
	SDL_Texture* sdlTexture = nullptr;
	//�ü���Χ�������������Ͻ���㣬����
	Math::rectangle_i rectRgn;

	//���캯��
	Texture(SDL_Texture* texture);
	Texture(SDL_Texture* texture, int x, int y, int w, int h);
	Texture(SDL_Texture* texture, const Math::rectangle_i& rgn);
	Texture(SDL_Texture* texture, const Vector2& size);
	//��������
	~Texture();

	//���òü���Χ
	void SetRectRgn(const Math::rectangle_i& rgn);
	// ��������͸����
	void SetTextureAlpha(uint8_t alpha);

	//��ȡ������
	inline int GetWidth() const {return rectRgn.w; }
	inline int GetHeight() const {return rectRgn.h; }
	Vector2 GetSize() const { return Vector2((float)rectRgn.w, (float)rectRgn.h); }
};

