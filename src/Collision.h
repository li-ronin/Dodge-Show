#pragma once
#include"SDL2/SDL.h"

class ColliderComponent;

class Collision
{
public:
	// 物体A和物体B是否发生碰撞
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);

	static bool AABB(const ColliderComponent& colA , const ColliderComponent& colB);
};