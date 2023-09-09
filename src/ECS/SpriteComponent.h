#pragma once
#include"Components.h"
#include"../TextureManager.h"
#include"SDL2/SDL.h"
#include"SDL_image.h"

/*
* SpriteComponent����ܰ�����Ⱦ���������λ����Ϣ���ߴ�ȡ�
* ������ʵ�����Ϊ�ɼ���ͼ�Ρ� ������Ⱦ��ҽ�ɫ�����
*/

class SpriteComponent : public Component 
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
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
		srcRect.h = 330;
		srcRect.w = 343;
		srcRect.x = 0;
		srcRect.y = 0;
		destRect.w = srcRect.w / 3;
		destRect.h = srcRect.h / 3;
	}
	void update() override
	{
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