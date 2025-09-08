#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

class Entity
{
public:
	//Construtor
	Entity(Vector3 startPos) : position(startPos) {}

	//Getters e setters
	Vector3 getPosition() const { return position; }
	void setPosition(Vector3 newPos) { position = newPos; }

	//funçoes virtuais para serem implementadas pelas classes filhas
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	Vector3 position;
	Color color;
};

#endif