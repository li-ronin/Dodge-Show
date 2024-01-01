#pragma once
#include"ECS.h"
#include"SDL2/SDL.h"
#include "../AssetManager.h"
// 图块
class TileComponent : public Component
{
public :
	// 皮肤
	SDL_Texture* texture;
	// 资源图片的位置 和 宽高（截取）
	SDL_Rect srcRect;
	// 显示在屏幕中的位置 和 宽高
	SDL_Rect destRect;
	// 图块的位置
	Vector2D tilePos;
	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tilesize, int tilescale, std::string texID)
	{

		//texture = TextureManager::LoadTexture(path);
		texture = Game::assets->GetTexture(texID);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tilesize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tilesize * tilescale;

		tilePos.x = xpos;
		tilePos.y = ypos;
	}	


	void update() override
	{
		// camera的(x, y)是相对位置的起始坐标
		destRect.x = tilePos.x - Game::camera.x;
		destRect.y = tilePos.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
