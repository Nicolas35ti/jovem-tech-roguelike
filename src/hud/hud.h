#ifndef HUD_H
#define HUD_H

#include "../entities/player.h"
#include "raylib.h"
#include <string>

class HUD
{
public:
	HUD(Player* p, bool* hasKey) : player(p), playerHaveKey(hasKey) {}
	void Draw();

private:
	Player* player;
	bool* playerHaveKey;
};

#endif