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
				transform->mousePos.x = Game::event.button.x + Game::camera.x - 40;
				transform->mousePos.y = Game::event.button.y + Game::camera.y - 70;
				if(transform->mousePos.x< transform->position.x)sprite->Play("left");
				else sprite->Play("right");
			}
		}

	}
	void draw()  override
	{

	}
private:

};