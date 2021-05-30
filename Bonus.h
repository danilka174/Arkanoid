#pragma once

#include "Ball.h"
#include "Field.h"

class Bonus { //����� �����
private:
	float radius;
	float x, y;

public:
	Bonus(float posX, float posY); //�����������
	~Bonus(void) {} //����������

	virtual void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) = 0; //����������� ������� ������������� ������

	bool Move(float userWindowHeight, std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field); //�������� ������
	void Draw(std::shared_ptr <sf::RenderWindow> window); //���������� �����
};

class ChangePlate :public Bonus { //����� ������, ������� ������ ������ ���������
public:
	ChangePlate(float posX, float posY) :Bonus(posX, posY) {} 
	~ChangePlate(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class ChangeBall :public Bonus { //����� ������, ������� ������ �������� ����
public:
	ChangeBall(float posX, float posY) :Bonus(posX, posY) {} 
	~ChangeBall(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class BallStick :public Bonus { //����� ������, ������� �������� �� ����������
public:
	BallStick(float posX, float posY) :Bonus(posX, posY) {}  
	~BallStick(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class BallBottom :public Bonus { //����� ������, ������� ��������� ���
public:
	BallBottom(float posX, float posY) :Bonus(posX, posY) {} 
	~BallBottom(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class RandomPath :public Bonus { //����� ������, ������� ������ ���������� ������
public:
	RandomPath(float posX, float posY) :Bonus(posX, posY) {} 
	~RandomPath(void) {} 

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override; 
};

class MovingBlockBonus :public Bonus { //����� ������, ������� ��������� ���������� ����
public:
	MovingBlockBonus(float posX, float posY) :Bonus(posX, posY) {} 
	~MovingBlockBonus(void) {}

	void Trigger(std::shared_ptr <Plate> plate, std::shared_ptr <Ball> ball, std::shared_ptr <Field> field) override;
};