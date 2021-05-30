#include "Plate.h"

#define BAR_SPEED 1

Plate::Plate(float plateHeight, float plateWidth, float posX, float posY) { //�����������
	height = plateHeight;
	width = plateWidth;
	defaultWidth = plateWidth;
	x = posX;
	y = posY;
	defaultX = posX;
	ballStick = 0;
}

float Plate::GetHeight(void) { //������ ���������
	return height;
}

float Plate::GetWidth(void) { //������ ��������� �� ������ ������
	return width;
}

float Plate::GetDefaultWidth(void) { //������ ��������� �� ���������
	return defaultWidth;
}

float Plate::GetPosX(void) { //������� ���������� �� �
	return x;
}

float Plate::GetPosY(void) { //������� ���������� �� Y
	return y;
}

unsigned Plate::GetBallStick(void) { //���������� ���������� ����
	return ballStick;
}

void Plate::SetWidth(float newWidth) { //������ ����� ������ ���������
	width = newWidth;
}

void Plate::SetBallStick(unsigned newBallStick) { //������ ����� ���������� ���������� ����
	ballStick += newBallStick;
}

void Plate::Move(float userWindowWidth) { //�������� ��������� � ������� ����������
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		if (x >= 0)
			x -= BAR_SPEED;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		if (x <= userWindowWidth - width)
			x += BAR_SPEED;
}

void Plate::BallOut(void) { //���� ��� �������
	width = defaultWidth;
	x = defaultX;
	ballStick = 0;
}

void Plate::Draw(std::shared_ptr <sf::RenderWindow> window) { //���������� ���������
	sf::RectangleShape shape(sf::Vector2f(width, height));

	shape.setFillColor(sf::Color:: Magenta);
	shape.setPosition(x, y);

	window->draw(shape);
}