#include "Ball.h"

#define DEFAULT_SPEED 3
#define CHANCE_OF_RANDOM 15
#define POINTS_OF_OUT -3

Ball::Ball(float ballRadius, float posX, float posY) { //�����������
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

float Ball::GetPosX(void) { //������� �� �
	return x;
}

void Ball::SetSpeed(float newSpeedX, float newSpeedY) { //������ ��������
	speedX *= newSpeedX;
	speedY *= newSpeedY;
}

void Ball::SetBallBottom(bool value) { //������ ���� �� ���
	ballBottom = value;
}

void Ball::SetBarOffset(float newOffset) { //������ ������� ���� ������������ ���������
	barOffset = newOffset;
}

void Ball::SetRandomPath(float newRandomPath) { //����������� ���� �������� ����������
	randomPath = newRandomPath;
}

int Ball::BallOut(float userWindowHeight, std::shared_ptr <Plate> plate) { //���� ��������� �� ������� ���
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

unsigned Ball::BallIsSticking(void) { //���� ��� ������ ���������� � ���������
	speedX = 0;
	speedY = 0;
	return 2;
}

void Ball::CollisionWithWindow(float userWindowWidth, float offsetHeight) { //��������� ������������ � ��������� ����
	float leftBoarder = abs(speedX);
	float rightBoarder = userWindowWidth - 2 * radius - speedX;
	float upperBoarder = offsetHeight - abs(speedY);

	if ((x < leftBoarder) || (x > rightBoarder))
		speedX *= -1;
	if (y < upperBoarder)
		speedY *= -1;
}

unsigned Ball::CollisionWithBlck(float shapeHeight, float shapeWidth, float shapeX, float shapeY, unsigned ballStick) { //��������� ������������ ���� � �������
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

	if ((x > leftBoarder) && (x < rightBoarder) && (withUpperBoarder || withLowerBoarder)) { //������������ ������������
		if (ballStick > 0)
			result = BallIsSticking();
		else {
			speedY *= -1;
			result = 1;
		}
	}

	if ((y < lowerBoarder) && (y > upperBoarder) && (withLeftBoarder || withRightBoarder)) { //�������������� ������������
		if (ballStick > 0)
			result = BallIsSticking();
		else {
			speedX *= -1;
			result = 1;
		}
	}

	if ((leftSide || rightSide) && (upperSide || lowerSide)) { //����������� �� ����
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

void Ball::BallMoveRandom(void) { //���� �������� ����� ��������� ����������
	if (randomPath && (rand() % 100 < CHANCE_OF_RANDOM)) {
		speedX *= (float)pow(-1, rand() % 2);
		speedY *= (float)pow(-1, rand() % 2);
		randomPath = false;
	}
}

void Ball::ZeroSpeed(std::shared_ptr <Plate> plate, float userWindowWidth) { //���� ��� �� ������
	if ((speedX == 0) && (speedY == 0)) {
		if (plate->GetBallStick() > 0)
			x = plate->GetPosX() + barOffset;
		else
			x = plate->GetPosX() + plate->GetWidth() / 2 - radius;

		y = plate->GetPosY() - 2 * radius;
		StartMove(userWindowWidth);
	}
}

void Ball::StartMove(float userWindowWidth) { //������ ������ �������� ��������
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		speedX = DEFAULT_SPEED * (defaultX - x) / userWindowWidth;
		speedY = -sqrt(DEFAULT_SPEED * DEFAULT_SPEED - speedX * speedX);
	}
}

void Ball::Move(std::shared_ptr <Plate> plate, float userWindowWidth) { //�������� ����
	BallMoveRandom();
	x += speedX;
	y += speedY;
	ZeroSpeed(plate, userWindowWidth);
}

void Ball::Draw(std::shared_ptr <sf::RenderWindow> window) { //���������� ���
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::White);
	circle.setPosition(x, y);

	window->draw(circle);
}