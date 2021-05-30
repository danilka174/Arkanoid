#pragma once

#include "Ball.h"
#include "Field.h"

class Bonus { //класс бонус
private:
	float radius;
	float x, y;

public:
	Bonus(float posX, float posY); //конструктор
	~Bonus(void) {} //деструктор

	virtual void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) = 0; //виртуальная функция использования бонуса

	bool Move(float userWindowHeight, std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field); //движение бонусп
	void Draw(std::shared_ptr <sf::RenderWindow> window); //нарисовать бонус
};

class ChangePlate :public Bonus { //класс бонуса, который меняет размер платформы
public:
	ChangePlate(float posX, float posY) :Bonus(posX, posY) {} 
	~ChangePlate(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class ChangeBall :public Bonus { //класс бонуса, который меняет скорость мяча
public:
	ChangeBall(float posX, float posY) :Bonus(posX, posY) {} 
	~ChangeBall(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class BallStick :public Bonus { //класс бонуса, который отвечает за прилипание
public:
	BallStick(float posX, float posY) :Bonus(posX, posY) {}  
	~BallStick(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class BallBottom :public Bonus { //класс бонуса, который блокирует дно
public:
	BallBottom(float posX, float posY) :Bonus(posX, posY) {} 
	~BallBottom(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class RandomPath :public Bonus { //класс бонуса, который меняет напрвление полета
public:
	RandomPath(float posX, float posY) :Bonus(posX, posY) {} 
	~RandomPath(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class MovingBlockBonus :public Bonus { //класс бонуса, который добавляет движущийся блок
public:
	MovingBlockBonus(float posX, float posY) :Bonus(posX, posY) {} 
	~MovingBlockBonus(void) {}

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override;
};