#include "game.h"
#include <string>

//Construtor da classe game
Game::Game(int width, int height)
:screenWidth(width), screenHeight(height), currentState(GAMEPLAY),
map(20, 20), player({0.0f, 0.5f, 0.0f}, "assets/obj.obj"), playerHaveKey(false) {
	InitGame();
}

//destrutor
Game::~Game() {}

//inicializa os componentes do jogo
void Game::InitGame()
{
	//Camera
	camera = { 0 };
	camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	UpdateCamera(&camera, CAMERA_FREE);

	//posições
	doorPos = { (float)map.getWidth() - 2.0f, 0.5f, 0.5f };
	keyPos = { (float)map.getWidth() / 2.0f, 0.5f, (float)map.getHeight() / 2.0f };

	//inimigos
	enemies.clear();
	enemies.emplace_back(Enemy({5.0f, 0.5f, 5.0f}));
	enemies.emplace_back(Enemy({10.0f, 0.5f, 8.0f}));
	enemies.emplace_back(Enemy({3.0f, 0.5f, 12.0f}));

	SetMousePosition(screenWidth/2, screenHeight/2);
	DisableCursor();

	hud = new HUD(&player, &playerHaveKey);
}

//lógica de atualizaçao a cada frame
void Game::Update()
{

	switch(currentState)
	{
	case GAMEPLAY:
		//movimentaçao do jogador
		player.Update();
		{
			//codigo barra de vida
			if (IsKeyPressed(KEY_H)) player.SetHP(player.GetHP() - 10); // Teste: perde 10 de HP
	        if (IsKeyPressed(KEY_J)) player.SetHP(player.GetHP() + 10); // Teste: ganha 10 de HP
	        player.ClampHP();

			//codigo camera POV
			Vector3 playerPos = player.getPosition();
			camera.position = { playerPos.x, playerPos.y + 1.7f, playerPos.z };

			//movimento do mouse
			Vector2 mousePos = GetMousePosition();
			mouseDelta.x = mousePos.x - screenWidth/2;
			mouseDelta.y = mousePos.y - screenHeight / 2;

			float sensivity = 0.003f;
			yaw -= mouseDelta.x * sensivity;
			pitch += mouseDelta.y * sensivity;

			//limitar a rotação vertical
			if (pitch > 1.5f) pitch = 1.5f;
			if (pitch > -1.5f) pitch = -1.5f;

			//resetar mouse para o centro
			SetMousePosition(screenWidth/2, screenHeight/2);

			//vetor de direção
			Vector3 forward = {
				cosf(pitch) * sinf(yaw),
				sinf(pitch),
				cosf(pitch) * cosf(yaw)
			};
			forward = Vector3Normalize(forward);

			//alinha o movimento do personagem ao eixo da camera
			Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, {0.0f, 1.0f, 0.0f}));
			player.Move(forward, right);
			player.SetRotation(forward);

			//atualiza camera POV
			camera.target = Vector3Add(camera.position, forward);
			camera.up = { 0.0f, 1.0f, 0.0f };
		}

		//logica de colisao com a chave
		if (!playerHaveKey && CheckCollisionSpheres(player.getPosition(), 0.5f, keyPos, 0.5f))
		{
			playerHaveKey = true;
		}

		//logica para colisao com a porta
		if (playerHaveKey && CheckCollisionSpheres(player.getPosition(), 0.5f, doorPos, 1.0f))
		{
			currentState = QUIZ;
			quiz.SelectNewQuestion();
		}
		break;

	case QUIZ:
		quiz.Update();
		if (quiz.CorrectAnswer())
		{
			currentState = VICTORY;
		} else if (quiz.WrongAnswer()){
			//penalidade por errar
			currentState = GAMEPLAY;
			quiz.Reset();
		}
		break;

	default:
		break;
	}
}

//logica de desenho a cada frame
void Game::Draw()
{
	BeginMode3D(camera);

	map.Draw();

	//desenha inimigos
	for (auto& enemy : enemies)
	{
		enemy.Draw();
	}

	//desenha a porta
	DrawCube(doorPos, 2.0f, 2.5f, 0.5f, BROWN);

	//desenha a chave
	if (!playerHaveKey)
	{
		DrawCube(keyPos, 0.5f, 0.5f, 0.5f, GOLD);
	}

	EndMode3D();

	hud->Draw();


	//interface(UI)
	if (currentState == QUIZ)
	{
		quiz.Draw();
	}

	if (currentState == VICTORY)
	{
		DrawText("VOCÊ VENCEU!", screenWidth / 2 - 150, screenHeight / 2 - 20, 40, GREEN);
	}
}