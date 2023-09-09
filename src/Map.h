#pragma once
#include<string>

class Map
{
public:
	Map();
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);

};