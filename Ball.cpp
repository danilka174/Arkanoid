#include "Ball.h"

#define DEFAULT_SPEED 3
#define CHANCE_OF_RANDOM 15
#define POINTS_OF_OUT -3

Ball::Ball(float ballRadius, float posX, float posY) { //конструктор
	radius = ballRadius;
	x = posX;
	y = posY;
	defaultX = posX;
	defaultY = posY;
	speedX = 0;
	speedY = 0;

	barOffset = 0;
	ballBottom = false;
	randomPath = false;
}

float Ball::GetPosX(void) { //позиция по Х
	return x;
}

void Ball::SetSpeed(float newSpeedX, float newSpeedY) { //задать скорость
	speedX *= newSpeedX;
	speedY *= newSpeedY;
}

void Ball::SetBallBottom(bool value) { //задать блок на дне
	ballBottom = value;
}

void Ball::SetBarOffset(float newOffset) { //задать позицию мяча относительно платформы
	barOffset = newOffset;
}

void Ball::SetRandomPath(float newRandomPath) { //возможность мяча изменить траекторию
	randomPath = newRandomPath;
}

int Ball::BallOut(float userWindowHeight, std::shared_ptr <Plate> plate) { //если платформа не поймала мяч
	float lowerBoarder = userWindowHeight - 2 * radius;

	if (y >= lowerBoarder) {
		if (!ballBottom) {
			speedX = 0;
			speedY = 0;
			x = defaultX;
			y = defaultY;
			randomPath = 0;

			plate->BallOut();
			return POINTS_OF_OUT;
		}
		else {
			speedY *= -1;
			ballBottom = false;
		}
	}
	return 0;
}

unsigned Ball::BallIsSticking(void) { //если мяч должен прилипнуть к платформе
	speedX = 0;
	speedY = 0;
	return 2;
}

void Ball::CollisionWithWindow(float userWindowWidth, float offsetHeight) { //обработка столкновений с границами окна
	float leftBoarder = abs(speedX);
	float rightBoarder = userWindowWidth - 2 * radius - speedX;
	float upperBoarder = offsetHeight - abs(speedY);

	if ((x < leftBoarder) || (x > rightBoarder))
		speedX *= -1;
	if (y < upperBoarder)
		speedY *= -1;
}

unsigned Ball::CollisionWithBlck(float shapeHeight, float shapeWidth, float shapeX, float shapeY, unsigned ballStick) { //обработка столкновений мяча с блоками
	unsigned result = 0;

	float leftBoarder = shapeX - 2 * radius;
	float rightBoarder = shapeX + shapeWidth;
	float upperBoarder = shapeY - 2 * radius;
	float lowerBoarder = shapeY + shapeHeight;

	float speed = sqrt(speedX * speedX + speedY * speedY);

	bool withUpperBoarder = (upperBoarder - y >= 0) && (upperBoarder - y < speedY);
	bool withLowerBoarder = (y - lowerBoarder >= 0) && (y - lowerBoarder < abs(speedY));
	bool withLeftBoarder = (leftBoarder - x >= 0) && (leftBoarder - x < speedX);
	bool withRightBoarder = (x - rightBoarder >= 0) && (x - rightBoarder < abs(speedX));

	bool upperSide = (upperBoarder - y >= 0) && (upperBoarder - y < speed);
	bool lowerSide = (y - lowerBoarder >= 0) && (y - lowerBoarder < speed);
	bool leftSide = (leftBoarder - x >= 0) && (leftBoarder - x < speed);
	bool rightSide = (x - rightBoarder >= 0) && (x - rightBoarder < speed);

	if ((x > leftBoarder) && (x < rightBoarder) && (withUpperBoarder || withLowerBoarder)) { //вертикальное столкновение
		if (ballStick > 0)
			result = BallIsSticking();
		else {
			speedY *= -1;
			result = 1;
		}
	}

	if ((y < lowerBoarder) && (y > upperBoarder) && (withLeftBoarder || withRightBoarder)) { //горизонтальное столкновение
		if (ballStick > 0)
			result = BallIsSticking();
		else {
			speedX *= -1;
			result = 1;
		}
	}

	if ((leftSide || rightSide) && (upperSide || lowerSide)) { //столкноение по углу
		if (ballStick > 0)
			result = BallIsSticking();
		else {
			speedX *= -1;
			speedY *= -1;
			result = 1;
		}
	}
	return result;
}

void Ball::BallMoveRandom(void) { //если сработал бонус изменения траектории
	if (randomPath && (rand() % 100 < CHANCE_OF_RANDOM)) {
		speedX *= (float)pow(-1, rand() % 2);
		speedY *= (float)pow(-1, rand() % 2);
		randomPath = false;
	}
}

void Ball::ZeroSpeed(std::shared_ptr <Plate> plate, float userWindowWidth) { //если мяч на спауне
	if ((speedX == 0) && (speedY == 0)) {
		if (plate->GetBallStick() > 0)
			x = plate->GetPosX() + barOffset;
		else
			x = plate->GetPosX() + plate->GetWidth() / 2 - radius;

		y = plate->GetPosY() - 2 * radius;
		StartMove(userWindowWidth);
	}
}

void Ball::StartMove(float userWindowWidth) { //задать начало движения пробелом
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		speedX = DEFAULT_SPEED * (defaultX - x) / userWindowWidth;
		speedY = -sqrt(DEFAULT_SPEED * DEFAULT_SPEED - speedX * speedX);
	}
}

void Ball::Move(std::shared_ptr <Plate> plate, float userWindowWidth) { //движение мяча
	BallMoveRandom();
	x += speedX;
	y += speedY;
	ZeroSpeed(plate, userWindowWidth);
}

void Ball::Draw(std::shared_ptr <sf::RenderWindow> window) { //нарисовать мяч
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::White);
	circle.setPosition(x, y);

	window->draw(circle);
}