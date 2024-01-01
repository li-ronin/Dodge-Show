#pragma once
#include "TextureManager.h"
#include "ECS/ECS.h"
#include "Vector2D.h"
#include <map>

class AssetManager {
public:
	AssetManager(Manager *manager);
	~AssetManager();
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:
	std::map<std::string, SDL_Texture*> textures;
};