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
	enemies.emplace_back(Enemy({0.5f, 9.5f, 0.5f}, EnemyType::Normal));
	enemies.emplace_back(Enemy({10.0f, 0.5f, 8.0f}, EnemyType::Fast));
	enemies.emplace_back(Enemy({15.0f, 0.5f, 6.0f}, EnemyType::Tank));
	enemies.emplace_back(Enemy({20.0f, 0.5f, 10.0f}, EnemyType::Boss));

	SetMousePosition(screenWidth/2, screenHeight/2);
	DisableCursor();

	hud = new HUD(&player, &playerHaveKey);
}

//=======FUNÇÂO DE DEBUG=========
void Game::HandleDebug()
{
	if (!debugMode) return;

	//spawn de inimigos
	if (IsKeyPressed(KEY_ONE))
	{
		enemies.emplace_back(Enemy(player.getPosition(), EnemyType::Normal));
	}
	if (IsKeyPressed(KEY_TWO))
	{
		enemies.emplace_back(Enemy(player.getPosition(), EnemyType::Fast));
	}
	if (IsKeyPressed(KEY_THREE))
	{
		enemies.emplace_back(Enemy(player.getPosition(), EnemyType::Tank));
	}
	if (IsKeyPressed(KEY_FOUR))
	{
		enemies.emplace_back(Enemy(player.getPosition(), EnemyType::Boss));
	}

	DrawText("DEBUG MODE ON", 10, screenHeight - 60, 20, RED);

	std::string info = "Enemies " + std::to_string(enemies.size()) + " | Player HP: " + std::to_string(player.GetHP());
	DrawText(info.c_str(), 10, screenHeight - 30, 20, BLACK);
}

//lógica de atualizaçao a cada frame
void Game::Update()
{

	HandleDebug();
	if (IsKeyPressed(KEY_F3)) debugMode = !debugMode;

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

	damageTimer -= GetFrameTime();
	if (damageTimer < 0.0f) damageTimer = 0.0f;

	for (auto& enemy : enemies)
	{
		enemy.Update(player.getPosition());
		if (damageTimer <= 0.0f &&
			CheckCollisionSpheres(player.getPosition(), 0.5f, enemy.getPosition(), 0.5f))
			{
				player.SetHP(player.GetHP() - enemy.getDamage());
				player.ClampHP();
				damageTimer = 1.0f;
			}
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

	if (debugMode) HandleDebug();


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

