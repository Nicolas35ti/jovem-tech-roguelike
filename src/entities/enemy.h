#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity
{
public:
	Enemy(Vector3 startPos);

	void Update() override;
	void Draw() override;
};

#endif