#pragma once
#include"ECS.h"
#include"Components.h"
#include"TransformComponent.h"
#include"SpriteComponent.h"

class TileComponent : public Component
{
public :
	TransformComponent* tileTransform;
	SpriteComponent* tileSprite;
	SDL_Rect tileRect;
	int tileID;
	const char* path;
	TileComponent() = default;
	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
		switch (id)
		{
		case 0:
			path = "assets/dirt.png";
			break;
		case 1:
			path = "assets/grass.png";
			break;
		case 2:
			path = "assets/wall.png";
			break;
		default:
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
		entity->addComponent<SpriteComponent>(path);
		tileTransform = &entity->getComponent<TransformComponent>();
		tileSprite = &entity->getComponent<SpriteComponent>();
	}
	void update() override 
	{
	
	}
	void draw() override
	{
	
	}
	
};
