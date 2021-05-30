#pragma once

#include "Plate.h"

class Ball { //����� ����
private:
	float radius;
	float x, y;
	float defaultX, defaultY;
	float speedX, speedY;
	float barOffset;

	bool ballBottom;
	bool randomPath;

public:
	Ball(float ballRadius, float posX, float posY); //�����������
	~Ball(void) {} //����������

	float GetPosX(void); //������� �� �

	void SetSpeed(float newSpeedX, float newSpeedY); //������ �������� ����
	void SetBallBottom(bool value); //������ ���� ���
	void SetBarOffset(float newOffset); //������ ������� ���� ������������ ���������
	void SetRandomPath(float newRandomPath); //����������� ���� �������� ����������

	int BallOut(float userWindowHeight, std::shared_ptr <Plate> plate); //���� ��������� �� ������� ���
	unsigned BallIsSticking(void); //���� ��� ������ � ���������
	void CollisionWithWindow(float userWindowWidth, float offsetHeight); //������������ ���� � ��������� ����
	unsigned CollisionWithBlck(float shapeHeight, float shapeWidth, float shapeX, float shapeY, unsigned ballStick = 0); //��������� ������������ ���� � �������

	void BallMoveRandom(void); //���� �������� ����� ��������� ����������
	void ZeroSpeed(std::shared_ptr <Plate> plate, float userWindowWidth); //���� ��� �� ������
	void StartMove(float userWindowWidth); //������ ��������
	void Move(std::shared_ptr <Plate> plate, float userWindowWidth); //�������� ����

	void Draw(std::shared_ptr <sf::RenderWindow> window); //���������� ���
};