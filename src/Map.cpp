#include "ECS/ECS.h"
#include"Map.h"
#include "Game.h"
#include "ECS/Components.h"
#include <fstream>


extern Manager manager;

Map::~Map()
{

}
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);
	int srcX, srcY;
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			srcY = atoi(&tile) * TileSize;
			mapFile.get(tile);
			srcX = atoi(&tile) * TileSize;
			AddTile(srcX, srcY, x * TileSize * MapScale, y * TileSize * MapScale);
			mapFile.ignore();// 清空输入
		}
	}
	mapFile.ignore();
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			if (tile == '1')
			{
				auto& tileCollision(manager.addEntity());
				tileCollision.addComponent<ColliderComponent>("terrain", x*(TileSize*MapScale), y * (TileSize * MapScale), TileSize * MapScale);
				tileCollision.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, TileSize, MapScale, texID);
	//将entity加入到它们各自的group中，然后按顺序渲染
	tile.addGroup(Game::groupMap);
}