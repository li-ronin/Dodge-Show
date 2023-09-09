#pragma once
#include"Game.h"

class GameObject
{
private:
	// 玩家的位置属性
	int xpos;
	int ypos;
	SDL_Texture* objTexture;		// 玩家的皮肤
	SDL_Rect	 srcRect, destRect;	// 玩家矩形框 source，destination

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();
	void init();
	void Update();
	void Render();
};