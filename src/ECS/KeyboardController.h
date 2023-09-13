#pragma once
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void update()  override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				std::cout << "w" << std::endl;
				transform->velocity.y = -1;
				break;
			case SDLK_a:
				std::cout << "a" << std::endl;
				transform->velocity.x = -1;
				sprite->change("assets/left.png", 3, 100);
				break;
			case SDLK_s:
				std::cout << "s" << std::endl;
				transform->velocity.y = 1;
				break;
			case SDLK_d:
				std::cout << "d" << std::endl;
				transform->velocity.x = 1;
				sprite->change("assets/right.png", 3, 100);
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			default:
				break;
			}
		}
	}
	void draw()  override
	{
	
	}
};