#include "enemy.h"

Enemy::Enemy(Vector3 startPos, EnemyType t) : Entity(startPos), type(t)
{
	switch(type)
	{
		case EnemyType::Normal: color = GREEN; break;
		case EnemyType::Fast: color = BLUE; break;
		case EnemyType::Tank: color = ORANGE; break;
		case EnemyType::Boss: color = RED; break;
	}
}

int Enemy::getDamage() const {
	switch (type)
	{
		case EnemyType::Normal: return 5;
		case EnemyType::Fast: return 8;
		case EnemyType::Tank: return 12;
		case EnemyType::Boss: return 25;
		default: return 1;
	}
}

Vector3 Enemy::getPosition() const
{
	return position;
}

void Enemy::Update(){
	//logica de ia vai aqui
}

void Enemy::Draw()
{
	DrawCube(position, 1.0f, 1.0f, 1.0f, color);
}
