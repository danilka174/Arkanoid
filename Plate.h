#pragma once

#include <SFML/Graphics.hpp>

class Plate { //����� ���������
private:
	float height, width;
	float defaultWidth;
	float x, y;
	float defaultX;
	unsigned ballStick;

public:
	Plate(float plateHeight, float plateWidth, float posX, float posY); //�����������
	~Plate(void) {} //����������

	float GetHeight(void); //������� ������ ���������
	float GetWidth(void); //������� ������ ���������
	float GetDefaultWidth(void); //������ ��������� �� ���������
	float GetPosX(void); //������� ���������� �� �
	float GetPosY(void); //������� ���������� �� Y
	unsigned GetBallStick(void); //���������� ���������� ����

	void SetWidth(float newWidth); //������ ����� ������ ���������
	void SetBallStick(unsigned newBallStick); //������ ����� ���������� ����������

	void Move(float userWindowWidth); //�������� ���������
	void BallOut(void); //����� ����

	void Draw(std::shared_ptr <sf::RenderWindow> window); //���������� ���������
};