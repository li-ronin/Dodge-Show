#pragma once
#include<string>

class Map
{
public:
	Map(std::string tID, int mapScale, int tileSize)
		:texID(tID), MapScale(mapScale), TileSize(tileSize)
	{}
	~Map();
	
	// this is new map system
	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
private:
	std::string texID;
	int MapScale;
	int TileSize;
};