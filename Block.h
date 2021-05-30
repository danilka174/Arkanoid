#pragma once

#include <SFML/Graphics.hpp>

class Block { //класс блока
protected:
	float height, width;
	float x, y;
	int health;
	sf::Color color;

public:
	Block(float blockHeight, float blockWidth, float posX, float posY, int blockHealth, sf::Color blockColor); //конструктор
	~Block(void) {} //деструктор

	float GetHeight(void); //высота блока
	float GetWidth(void); //ширина блока
	float GetPosX(void); //координата по Х
	float GetPosY(void); //координата по Y
	int GetHealth(void); //количество жизней блока
	sf::Color GetColor(void); //цвет блока

	void SetHealth(int addition); //задать количество жизней блока

	virtual float GetSpeedX(void) { return 0; } //виртуальная функция
	virtual void SetSpeedX(float newSpeedX) {} //виртуальная функция
	virtual void Move(float userWindowWidth) {} //виртуальная функция

	void Draw(std::shared_ptr <sf::RenderWindow> window); //нарисовать блок
};

class MovingBlock :public Block { //наследственный класс - движущийся бонус
private:
	float speedX;

public:
	MovingBlock(float brickHeight, float brickWidth, float posX, float posY); //конструктор
	~MovingBlock(void) {} //деструктор

	float GetSpeedX(void) override; //скорость движущегося блока
	void SetSpeedX(float newSpeedX) override;  //изменение направления скорости движущегося блока
	void Move(float userWindowWidth) override; //движение движущегося блока
};