#pragma once

#include <SFML/Graphics.hpp>

class Block { //����� �����
protected:
	float height, width;
	float x, y;
	int health;
	sf::Color color;

public:
	Block(float blockHeight, float blockWidth, float posX, float posY, int blockHealth, sf::Color blockColor); //�����������
	~Block(void) {} //����������

	float GetHeight(void); //������ �����
	float GetWidth(void); //������ �����
	float GetPosX(void); //���������� �� �
	float GetPosY(void); //���������� �� Y
	int GetHealth(void); //���������� ������ �����
	sf::Color GetColor(void); //���� �����

	void SetHealth(int addition); //������ ���������� ������ �����

	virtual float GetSpeedX(void) { return 0; } //����������� �������
	virtual void SetSpeedX(float newSpeedX) {} //����������� �������
	virtual void Move(float userWindowWidth) {} //����������� �������

	void Draw(std::shared_ptr <sf::RenderWindow> window); //���������� ����
};

class MovingBlock :public Block { //�������������� ����� - ���������� �����
private:
	float speedX;

public:
	MovingBlock(float brickHeight, float brickWidth, float posX, float posY); //�����������
	~MovingBlock(void) {} //����������

	float GetSpeedX(void) override; //�������� ����������� �����
	void SetSpeedX(float newSpeedX) override;  //��������� ����������� �������� ����������� �����
	void Move(float userWindowWidth) override; //�������� ����������� �����
};