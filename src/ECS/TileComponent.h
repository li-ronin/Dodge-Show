#pragma once
#include"ECS.h"
#include"SDL2/SDL.h"

// ͼ��
class TileComponent : public Component
{
public :
	// Ƥ��
	SDL_Texture* texture;
	// ��ԴͼƬ��λ�� �� ��ߣ���ȡ��
	SDL_Rect srcRect;
	// ��ʾ����Ļ�е�λ�� �� ���
	SDL_Rect destRect;
	// ͼ���λ��
	Vector2D tilePos;
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

		tilePos.x = xpos;
		tilePos.y = ypos;
	}	


	void update() override
	{
		// camera��(x, y)�����λ�õ���ʼ����
		destRect.x = tilePos.x - Game::camera.x;
		destRect.y = tilePos.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
