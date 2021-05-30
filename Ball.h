#pragma once

#include "Plate.h"

class Ball { //класс м€ча
private:
	float radius;
	float x, y;
	float defaultX, defaultY;
	float speedX, speedY;
	float barOffset;

	bool ballBottom;
	bool randomPath;

public:
	Ball(float ballRadius, float posX, float posY); //конструктор
	~Ball(void) {} //деструктор

	float GetPosX(void); //позици€ по ’

	void SetSpeed(float newSpeedX, float newSpeedY); //задать скорость м€ча
	void SetBallBottom(bool value); //задать блок дна
	void SetBarOffset(float newOffset); //задать позицию м€ча относительно платформы
	void SetRandomPath(float newRandomPath); //возможномть м€ча изменить траекторию

	int BallOut(float userWindowHeight, std::shared_ptr <Plate> plate); //если платформа не поймала м€ч
	unsigned BallIsSticking(void); //если м€ч прилип к платформе
	void CollisionWithWindow(float userWindowWidth, float offsetHeight); //столкновение м€ча с границами окна
	unsigned CollisionWithBlck(float shapeHeight, float shapeWidth, float shapeX, float shapeY, unsigned ballStick = 0); //обработка столкновени€ м€ча с блоками

	void BallMoveRandom(void); //если сработал бонус изменени€ траектории
	void ZeroSpeed(std::shared_ptr <Plate> plate, float userWindowWidth); //если м€ч на спауне
	void StartMove(float userWindowWidth); //начало движени€
	void Move(std::shared_ptr <Plate> plate, float userWindowWidth); //движение м€ча

	void Draw(std::shared_ptr <sf::RenderWindow> window); //нарисовать м€ч
};