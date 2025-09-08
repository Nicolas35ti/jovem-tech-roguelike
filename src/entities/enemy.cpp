#include "enemy.h"

Enemy::Enemy(Vector3 startPos) : Entity(startPos)
{
	color = RED;
}

void Enemy::Update(){
	//logica de ia vai aqui
}

void Enemy::Draw()
{
	DrawCube(position, 1.0f, 1.0f, 1.0f, color);
}