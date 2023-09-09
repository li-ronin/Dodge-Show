#pragma once
#include<string>

class Map
{
public:
	Map();
	~Map();
	// this is new map system
	void LoadMap(std::string path, int sizeX, int sizeY);

};