#pragma once
#include "Components.h"

class MouseController : public Component {
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

		if (SDL_MOUSEBUTTONDOWN == Game::event.type)
		{
			if (SDL_BUTTON_RIGHT == Game::event.button.button)
			{
				transform->mousePos.x = Game::event.button.x;
				transform->mousePos.y = Game::event.button.y;
			}
		}

	}
	void draw()  override
	{

	}

};