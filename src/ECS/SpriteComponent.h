#pragma once
#include"Components.h"
#include"../TextureManager.h"
#include"SDL2/SDL.h"
#include"SDL_image.h"

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
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	SpriteComponent(const char* path, int nFrames, int mSpeed)
	{
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTex(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void change(const char* path, int nFrames, int mSpeed)
	{
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTex(path);
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


		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};