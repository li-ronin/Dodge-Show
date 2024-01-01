#pragma once

#include"ECS.h"
#include"Components.h"
#include"SDL2/SDL.h"
#include"TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* CollisionTex;
	SDL_Rect CollSrcRect;
	SDL_Rect CollDestRect;

	TransformComponent* transform;
	ColliderComponent(std::string type)
	{
		tag = type;
	}	
	ColliderComponent(std::string type, int x, int y)
	{
		tag = type;
		collider.x = x;
		collider.y = y;
	}	
	ColliderComponent(std::string type, int x, int y, int size)
	{
		tag = type;
		collider.x = x;
		collider.y = y;
		collider.w = collider.h = size;
	}
	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		
		CollisionTex = TextureManager::LoadTexture("assets/CollisionTex.png");
		CollSrcRect = { 0, 0, 32, 32 };
		CollDestRect = { collider.x, collider.y, collider.w, collider.h };
		
	}
	void update() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		CollDestRect.x = collider.x - Game::camera.x;
		CollDestRect.y = collider.y - Game::camera.y;
		

		
	}
	void draw() override
	{
		TextureManager::Draw(CollisionTex, CollSrcRect, CollDestRect);
	}
};