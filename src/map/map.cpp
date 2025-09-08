#include "map.h"

Map::Map(int width, int height) : mapWidth(width), mapHeight(height)
{
	//logica de geração procedural
}

void Map::Draw() {
	//chao simples com grid
	DrawGrid(mapWidth, 1.0f);
}