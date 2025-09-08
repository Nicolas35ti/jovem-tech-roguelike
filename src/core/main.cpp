#include "raylib.h"
#include "game.h"

int main(void)
{
	//INICIA
	const int screenWidth = 1280;
	const int screenHeight = 720;

	//Inicializa a janela e o openGL
	InitWindow(screenWidth, screenHeight, "Jovem Tech v0.1");

	//Cria a instancia do jogo
	Game game(screenWidth, screenHeight);

	//define a taxa de quadros por segundo
	SetTargetFPS(60);

	//LOOP PRINCIPAL DO JOGO
	while (!WindowShouldClose())
	{
		//atualiza
		game.Update();

		//desenha
		BeginDrawing();

		ClearBackground(RAYWHITE); //limpa o fundo com uma cor

		game.Draw();

		EndDrawing();
	}

	//finalização
	CloseWindow();
	return 0;
}