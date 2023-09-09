#pragma once
#include"Game.h"

class GameObject
{
private:
	// ��ҵ�λ������
	int xpos;
	int ypos;
	SDL_Texture* objTexture;		// ��ҵ�Ƥ��
	SDL_Rect	 srcRect, destRect;	// ��Ҿ��ο� source��destination

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();
	void init();
	void Update();
	void Render();
};