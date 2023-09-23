#pragma once
#include"ECS.h"
#include"SDL2/SDL.h"

class TileComponent : public Component
{
public :
	// 皮肤
	SDL_Texture* texture;
	// 资源图片的位置 和 宽高（截取）
	SDL_Rect srcRect;
	// 显示在屏幕中的位置 和 宽高
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
