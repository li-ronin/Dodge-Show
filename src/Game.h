#pragma once

#include<stdio.h>
#include<iostream>
#include<vector>
#include"SDL2/SDL.h"
#include"SDL_image.h"

// 这里只能用声明，引ColliderComponent的头文件会有循环依赖冲突，导致Game类及所有成员在其他文件中不可用
class ColliderComponent; 

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running()
	{
		return isRunning;
	}
	static void AddTile(int srcX, int srcY, int xpos, int ypos);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	static bool isRunning;
	static SDL_Rect camera;
private:
	int count;
	SDL_Window* window;
	SDL_Texture* backgroundTexture;
	
};