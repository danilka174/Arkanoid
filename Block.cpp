#include "Block.h"

#define BRICK_SPEED (float)0.5

Block::Block(float blockHeight, float blockWidth, float posX, float posY, int blockHealth, sf::Color blockColor) { //конструктор
    height = blockHeight;
    width = blockWidth;
	health = blockHealth;
	color = blockColor;
    x = posX;
    y = posY;
}

float Block::GetHeight(void) { //высота блока
    return height;
}

float Block::GetWidth(void) { //ширина блока
    return width;
}

float Block::GetPosX(void) { //координата по Х
    return x;
}

float Block::GetPosY(void) { //координата по Y 
    return y;
}

int Block::GetHealth(void) { //количество жизней блока
    return health;
}

sf::Color Block::GetColor(void) { //цвет блока
    return color;
}

void Block::SetHealth(int add) { //задать количество жизней блока
    health += add;
}

float MovingBlock::GetSpeedX(void) { //скорость движущегося блока
    return speedX;
}

void MovingBlock::SetSpeedX(float newSpeedX) { //задать направление скорости движущегося блока
    speedX *= newSpeedX;
}

void MovingBlock::Move(float userWindowWidth) { //движение движущегося блока
    if (x <= 0 || x + width >= userWindowWidth)
        speedX *= -1;
    x += speedX;
}

void Block::Draw(std::shared_ptr <sf::RenderWindow> window) { //нарисовать блок
	sf::RectangleShape shape(sf::Vector2f(width, height));

	shape.setFillColor(color);
	shape.setPosition(x, y);
	shape.setOutlineThickness((height + width) / -40);
	shape.setOutlineColor(sf::Color::Black);

	window->draw(shape);
}

MovingBlock::MovingBlock(float blockHeight, float blockWidth, float posX, float posY) : Block(blockHeight, blockWidth, posX, posY, 3, sf::Color::Blue) { //конструктор
	speedX = BRICK_SPEED * (float)pow(-1, rand() % 2);
}
