#include "hud.h"

void HUD::Draw()
{
	//barra de vida
	float hpRatio = (float)player->GetHP() / player->GetMaxHP();
	DrawRectangle(350, 50, 100, 20, RED);
	DrawRectangle(350, 50, 100 * hpRatio, 20, GREEN);
	DrawRectangleLines(350, 50, 100, 20, BLACK);

	std::string textKey = "Chave: " + std::string(*playerHaveKey ? "Sim" : "Nao");
	DrawText(textKey.c_str(), 10, 10, 20, BLACK);
}