#pragma once
#include "Components.h"
#include "../Vector2D.h"


class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	Vector2D mousePos;
	int height = 32;
	int width = 32;
	float scale = 1;     // 玩家大小

	int speed = 10;
	TransformComponent() 
	{
		position.Zero();
	}
	TransformComponent(float sc)
	{
		// 初始化玩家位置 800*640
		//position.Zero();
		position.x = 400;
		position.y = 320;
		scale = sc;
	}
	TransformComponent(float x, float y) 
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, int h, int w, float sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	void init() override
	{
		velocity.Zero();
	}
	void update() override
	{
		//position.x += velocity.x * speed;
		//position.y += velocity.y * speed;
		float deltaX = mousePos.x - position.x;
		float deltaY = mousePos.y - position.y;
		float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
		if (distance > speed)
		{
			float ratio = speed / distance;
			position.x += (ratio * deltaX);
			position.y += (ratio * deltaY);
		}
		else
		{
			position.x = mousePos.x;
			position.y = mousePos.y;
		}
		if (distance != 0)
		{
			std::cout << distance << std::endl;
			std::cout << "mousePos: " << mousePos.x << ", " << mousePos.y << std::endl;
			std::cout << "position: " << position.x << ", " << position.y << std::endl;
			std::cout << "-----------------" << std::endl;
		}

	}

};