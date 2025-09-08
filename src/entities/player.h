#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "raylib.h"
#include "raymath.h"

class Player : public Entity
{
public:
	Model model;
	Player(Vector3 startPos, const char* modelPath);

	~Player();


	int GetHP()const { return hp; }
	int GetMaxHP() const { return maxHp; }
	void SetHP(int value) {
		if (value < 0) hp = 0;
		else if (value > maxHp) hp = maxHp;
		else hp = value;
	}

	void Update() override;
	void Draw() override;
	void Move(Vector3 forward, Vector3 right);
	void SetRotation(Vector3 forward);
	void ClampHP();

private:
	int hp;
	int maxHp;
	float speed = 5.0f;
	Vector3 rotation = {0.0f, 0.0f, 0.0f};
};

#endif