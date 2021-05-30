#include "Block.h"

#define BRICK_SPEED (float)0.5

Block::Block(float blockHeight, float blockWidth, float posX, float posY, int blockHealth, sf::Color blockColor) { //�����������
    height = blockHeight;
    width = blockWidth;
	health = blockHealth;
	color = blockColor;
    x = posX;
    y = posY;
}

float Block::GetHeight(void) { //������ �����
    return height;
}

float Block::GetWidth(void) { //������ �����
    return width;
}

float Block::GetPosX(void) { //���������� �� �
    return x;
}

float Block::GetPosY(void) { //���������� �� Y 
    return y;
}

int Block::GetHealth(void) { //���������� ������ �����
    return health;
}

sf::Color Block::GetColor(void) { //���� �����
    return color;
}

void Block::SetHealth(int add) { //������ ���������� ������ �����
    health += add;
}

float MovingBlock::GetSpeedX(void) { //�������� ����������� �����
    return speedX;
}

void MovingBlock::SetSpeedX(float newSpeedX) { //������ ����������� �������� ����������� �����
    speedX *= newSpeedX;
}

void MovingBlock::Move(float userWindowWidth) { //�������� ����������� �����
    if (x <= 0 || x + width >= userWindowWidth)
        speedX *= -1;
    x += speedX;
}

void Block::Draw(std::shared_ptr <sf::RenderWindow> window) { //���������� ����
	sf::RectangleShape shape(sf::Vector2f(width, height));

	shape.setFillColor(color);
	shape.setPosition(x, y);
	shape.setOutlineThickness((height + width) / -40);
	shape.setOutlineColor(sf::Color::Black);

	window->draw(shape);
}

MovingBlock::MovingBlock(float blockHeight, float blockWidth, float posX, float posY) : Block(blockHeight, blockWidth, posX, posY, 3, sf::Color::Blue) { //�����������
	speedX = BRICK_SPEED * (float)pow(-1, rand() % 2);
}
