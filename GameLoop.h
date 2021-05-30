#pragma once

#include "Bonus.h"

class GameLoop { //класс игрового цикла
private:
	int score;

	std::shared_ptr <sf::RenderWindow> window;
	std::shared_ptr <Field> field;
	std::shared_ptr <Plate> plate;
	std::shared_ptr <Ball> ball;
	std::vector <std::shared_ptr<Bonus>> bonusesMatrix;

public:
	GameLoop(void); //конструктор
	~GameLoop(void) {} //деструктор

	void Start(void); //главный игровой цикл
	void AllMovement(void); //все движения в игре
	void AllColisions(void); //проверка всех столкновений
	void AllDrawing(void); //нарисовать все игровые элементы

	void CollisionWithBlocks(void); //полная обработка столкновения с блоками

	void ChooseBonus(float bonusX, float bonusY); //выбрать бонус
	void StickingWork(void); //прилипание мяча
	void BonusesWork(void); //работа бонусов

	void CreateText(void); //счет игры

	void End(void); //конец игры
};