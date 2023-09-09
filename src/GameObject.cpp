#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* textureSheet, int x, int y)
{

	objTexture = TextureManager::LoadTexture(textureSheet);	// renderer��Game���еĶ������Ⱦ��
	xpos = x;
	ypos = y;
}
GameObject::~GameObject()
{
}
void GameObject::init()
{
	srcRect.h = 330;
	srcRect.w = 343;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = srcRect.w / 3;
	destRect.h = srcRect.h / 3;
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	destRect.x = xpos;
	destRect.y = ypos;


}
void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}