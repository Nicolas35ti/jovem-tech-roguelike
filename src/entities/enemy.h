#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

enum class EnemyType
{
	Normal,
	Fast,
	Tank,
	Boss
};

class Enemy : public Entity
{
public:
	Enemy(Vector3 startPos, EnemyType type);

	void Update() override;
	void Draw() override;

	Vector3 getPosition() const;

	int getDamage() const;
	EnemyType getType() const { return type; }

private:
	EnemyType type;
	Color color;
};

#endif
