#ifndef MAP_H
#define MAP_H

#include "raylib.h"

class Map
{
public:
	Map(int width, int height);
	void Draw();

	int getWidth() const { return mapWidth; }
	int getHeight() const { return mapHeight; }

private:
	int mapWidth;
	int mapHeight;
};

#endif