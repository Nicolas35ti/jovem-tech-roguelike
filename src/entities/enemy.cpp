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

void Enemy::Update()
{
}


void Enemy::Update(const Vector3& playerPos){
	Vector3 dir = Vector3Subtract(playerPos, position);
	dir = Vector3Normalize(dir);

	float speed = 0.2f;
	switch(type)
	{
		case EnemyType::Normal: speed = 0.02f; break;
		case EnemyType::Fast: speed = 0.05f; break;
		case EnemyType::Tank: speed = 0.01f; break;
		case EnemyType::Boss: speed = 0.015f; break;
		default: break;
	}

	position.x += dir.x * speed;
	position.z += dir.z * speed;
	position.y += dir.y * speed;
}

void Enemy::Draw()
{
	DrawCube(position, 1.0f, 1.0f, 1.0f, color);
}
