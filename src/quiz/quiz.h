#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <vector>
#include "raylib.h"

struct Question
{
	std::string enunciado;
	std::vector<std::string> options;
	int correctAnswerIndex;
};

class Quiz
{
public:
	Quiz();
	void Update();
	void Draw();
	void SelectNewQuestion();

	bool CorrectAnswer() const { return answerIsCorrect; }
	bool WrongAnswer() const { return answerIsWrong; }
	void Reset();

private:
	std::vector<Question> bancoDePerguntas;
	Question actualQuestion;
	int actualQuestionIndex;
	bool answerIsCorrect;
	bool answerIsWrong;
};

#endif