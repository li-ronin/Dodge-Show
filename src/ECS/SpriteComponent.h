#pragma once
#include"Components.h"
#include"../TextureManager.h"
#include"SDL2/SDL.h"
#include"SDL_image.h"
#include"Animation.h"
#include<map>
/*
* SpriteComponent类可能包含渲染所需的纹理、位置信息、尺寸等。
* 它负责将实体呈现为可见的图形。 用于渲染玩家角色的外观
*/

class SpriteComponent : public Component 
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frames = 0;		// 帧数
	int speed = 100;	// 每帧之间的延迟，单位ms
	
public:
	int animIndex = 0;
	std::map<const char*, Animation>animations;
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;
		Animation right(0, 3, 100);
		Animation left(1, 3, 100);
		animations.emplace("right", right);
		animations.emplace("left", left);
		
		//Play("left");
		Play("right");
		setTex(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		transform = &(entity->getComponent<TransformComponent>());
		srcRect.h = transform->height;
		srcRect.w = transform->width;
		srcRect.x = 0;
		srcRect.y = 0;

	}
	void update() override
	{

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%frames);
		}
		srcRect.y = animIndex * transform->height;//animIndex表示帧数在PNG中的第几行
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
		
	}
};