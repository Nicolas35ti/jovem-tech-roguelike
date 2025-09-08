#include "quiz.h"

Quiz::Quiz() : actualQuestionIndex(-1), answerIsCorrect(false), answerIsWrong(false)
{
	//banco de perguntas
	bancoDePerguntas = {
		{
			"Qual a palavra-chave para definir uma funcao em Python?",
			{"func", "def", "function", "define"},
			1
		},
		{
			"Qual o tipo de dado e usado para armazenar uma sequencia instavel de itens?",
			{"list", "dict", "set", "tuple"},
			3
		},
		{
			"Como voce escreve um comentario de uma linha em Python?",
			{"// Comentario", "/* Comentario */", "# Comentario", "<!-- comentario -->"},
			2
		}
	};
}

void Quiz::SelectNewQuestion()
{
	//seleciona uma pergunta aleatoria do banco de perguntas
	actualQuestionIndex = GetRandomValue(0, bancoDePerguntas.size() -1);
	actualQuestion = bancoDePerguntas[actualQuestionIndex];
	Reset();
}

void Quiz::Update()
{
	//verifica qual a opção foi selecionada
	int selectionedAnswer = -1;
	if (IsKeyPressed(KEY_ONE)) selectionedAnswer = 0;
    if (IsKeyPressed(KEY_TWO)) selectionedAnswer = 1;
    if (IsKeyPressed(KEY_THREE)) selectionedAnswer = 2;
    if (IsKeyPressed(KEY_FOUR)) selectionedAnswer = 3;

    if (selectionedAnswer != -1)
    {
    	if (selectionedAnswer == actualQuestion.correctAnswerIndex)
    	{
    		answerIsCorrect = true;
    	} else {
    		answerIsWrong = true;
    	}
    }
}

void Quiz::Draw()
{
	//desenha a interface do quiz no centro da tela
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(GRAY, 0.8f));
	DrawText(actualQuestion.enunciado.c_str(), 100, 100, 20, WHITE);

	for (size_t i = 0; i < actualQuestion.options.size(); ++i)
	{
		std::string textOption = std::to_string(i + 1) + ". " + actualQuestion.options[i];
		DrawText(textOption.c_str(), 120, 150 + i + 40, 20, WHITE);
	}
}

void Quiz::Reset()
{
	answerIsCorrect = false;
	answerIsCorrect = false;
}