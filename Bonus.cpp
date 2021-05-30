#include "Bonus.h"

#define CHANGE_NUM (float)1.5
#define BONUS_SPEED 1
#define STICKING 3

Bonus::Bonus(float posX, float posY) { //конструктор
	radius = 5;
	x = posX;
	y = posY;
}

bool Bonus::Move(float userWindowHeight, std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) { //движение бонуса
	float leftBoarder = plate->GetPosX() - 2 * radius;
	float rightBoarder = plate->GetPosX() + plate->GetWidth();
	float upperBoarder = plate->GetPosY() - 2 * radius;
	float lowerBoarder = plate->GetPosY() + plate->GetHeight();
	float bonusOut = userWindowHeight - BONUS_SPEED;

	y += BONUS_SPEED;

	if ((x >= leftBoarder) && (x <= rightBoarder) && (y >= upperBoarder) && (y <= lowerBoarder))
	{
		Trigger(plate, ball, field);
		return true;
	}
	else if (y >= bonusOut)
		return true;
	return false;
}

void Bonus::Draw(std::shared_ptr <sf::RenderWindow> window) { //нарисовать бонус
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(x, y);

	window->draw(circle);
}

void ChangePlate::Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) { //изменяет размер платформы
	switch (rand() % 2) {
	case 0:
		if (plate->GetWidth() > plate->GetDefaultWidth() / CHANGE_NUM)
			plate->SetWidth(plate->GetDefaultWidth() / CHANGE_NUM);
		break;
	case 1:
		if (plate->GetWidth() < plate->GetDefaultWidth() * CHANGE_NUM)
			plate->SetWidth(plate->GetDefaultWidth() * CHANGE_NUM);
		break;
	}
}

void ChangeBall::Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) { //изменяет скорость мяча
	switch (rand() % 2) {
	case 0:
		ball->SetSpeed(1 / CHANGE_NUM, 1 / CHANGE_NUM);
		break;
	case 1:
		ball->SetSpeed(CHANGE_NUM, CHANGE_NUM);
		break;
	}
}

void BallStick::Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) { //мяч прилипает к платформе
	plate->SetBallStick(STICKING);
}

void BallBottom::Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) { //блок на дно
	ball->SetBallBottom(true);
}

void RandomPath::Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) { //меняет траекторию полета
	ball->SetRandomPath(true);
}

void MovingBlockBonus::Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) { //появление двжущегося блока
	field->SetMovingBlock();
}