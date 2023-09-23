#pragma once
#include"ECS.h"
#include"SDL2/SDL.h"

class TileComponent : public Component
{
public :
	// Ƥ��
	SDL_Texture* texture;
	// ��ԴͼƬ��λ�� �� ��ߣ���ȡ��
	SDL_Rect srcRect;
	// ��ʾ����Ļ�е�λ�� �� ���
	SDL_Rect destRect;

	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 64;
	}	
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
