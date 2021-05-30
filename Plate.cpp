#include "Plate.h"

#define BAR_SPEED 1

Plate::Plate(float plateHeight, float plateWidth, float posX, float posY) { //конструктор
	height = plateHeight;
	width = plateWidth;
	defaultWidth = plateWidth;
	x = posX;
	y = posY;
	defaultX = posX;
	ballStick = 0;
}

float Plate::GetHeight(void) { //высота платформы
	return height;
}

float Plate::GetWidth(void) { //ширина платформы на данный момент
	return width;
}

float Plate::GetDefaultWidth(void) { //ширина платформы по умолчанию
	return defaultWidth;
}

float Plate::GetPosX(void) { //текущие координаты по ’
	return x;
}

float Plate::GetPosY(void) { //текущие координаты по Y
	return y;
}

unsigned Plate::GetBallStick(void) { //количество прилипаний м€ча
	return ballStick;
}

void Plate::SetWidth(float newWidth) { //задать новую ширину платформы
	width = newWidth;
}

void Plate::SetBallStick(unsigned newBallStick) { //задать новое количество прилипаний м€ча
	ballStick += newBallStick;
}

void Plate::Move(float userWindowWidth) { //движение платформы с помощью клавиатуры
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		if (x >= 0)
			x -= BAR_SPEED;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		if (x <= userWindowWidth - width)
			x += BAR_SPEED;
}

void Plate::BallOut(void) { //если м€ч вылетел
	width = defaultWidth;
	x = defaultX;
	ballStick = 0;
}

void Plate::Draw(std::shared_ptr <sf::RenderWindow> window) { //нарисовать платформу
	sf::RectangleShape shape(sf::Vector2f(width, height));

	shape.setFillColor(sf::Color:: Magenta);
	shape.setPosition(x, y);

	window->draw(shape);
}