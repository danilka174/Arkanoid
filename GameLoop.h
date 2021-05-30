#pragma once

#include "Bonus.h"

class GameLoop { //����� �������� �����
private:
	int score;

	std::shared_ptr <sf::RenderWindow> window;
	std::shared_ptr <Field> field;
	std::shared_ptr <Plate> plate;
	std::shared_ptr <Ball> ball;
	std::vector <std::shared_ptr<Bonus>> bonusesMatrix;

public:
	GameLoop(void); //�����������
	~GameLoop(void) {} //����������

	void Start(void); //������� ������� ����
	void AllMovement(void); //��� �������� � ����
	void AllColisions(void); //�������� ���� ������������
	void AllDrawing(void); //���������� ��� ������� ��������

	void CollisionWithBlocks(void); //������ ��������� ������������ � �������

	void ChooseBonus(float bonusX, float bonusY); //������� �����
	void StickingWork(void); //���������� ����
	void BonusesWork(void); //������ �������

	void CreateText(void); //���� ����

	void End(void); //����� ����
};