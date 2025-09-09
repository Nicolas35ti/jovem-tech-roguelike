#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "raymath.h"
#include "../entities/player.h"
#include "../entities/enemy.h"
#include "../hud/hud.h"
#include "../map/map.h"
#include "../quiz/quiz.h"
#include <vector>

//enum que controla os diferentes estados do jogo
enum GameState
{
	GAMEPLAY,
	QUIZ,
	GAME_OVER,
	VICTORY
};

class Game
{
public:
	//Construtor de destrutor
	Game(int screenWidth, int screenHeight);
	~Game();

	//funções principais do loop do jogo
	void Update();
	void Draw();
	void HandleDebug();

private:
	//VARIAVEIS DO JOGO
	int screenWidth;
	int screenHeight;
	GameState currentState;
	Camera3D camera;

	//OBJETOS DO JOGO
	Player player;
	std::vector<Enemy> enemies;
	Map map;
	HUD* hud;
	Quiz quiz;
	Vector3 doorPos;
	Vector3 keyPos;
	Vector2 mouseDelta = {0, 0};
	float yaw = 0.0f;
	float pitch = 0.0f;

	bool playerHaveKey;

	float damageTimer = 0.0f;

	//funções auxiliares
	void InitGame();
	void ResetGame();

	//-----DEBUG MODD-----
	bool debugMode = true;
};

#endif
