#pragma once

#include <SFML/Graphics.hpp>

class Plate { //класс платформы
private:
	float height, width;
	float defaultWidth;
	float x, y;
	float defaultX;
	unsigned ballStick;

public:
	Plate(float plateHeight, float plateWidth, float posX, float posY); //конструктор
	~Plate(void) {} //деструктор

	float GetHeight(void); //текуща€ высота платформы
	float GetWidth(void); //текуща€ ширина платформы
	float GetDefaultWidth(void); //ширина платформы по умолчанию
	float GetPosX(void); //текуща€ координата по ’
	float GetPosY(void); //текуща€ координата по Y
	unsigned GetBallStick(void); //количество прилипаний м€ча

	void SetWidth(float newWidth); //задать новую ширину платформы
	void SetBallStick(unsigned newBallStick); //задать новое количество прилипаний

	void Move(float userWindowWidth); //движение платформы
	void BallOut(void); //вылет м€ча

	void Draw(std::shared_ptr <sf::RenderWindow> window); //нарисовать платформу
};