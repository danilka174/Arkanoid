#pragma once
#include <array>

#include "Block.h"

class Field { //����� �������� ����
private:
	float height, width;
	float offset;
	unsigned blocksInRow, blocksInColumn;
	unsigned numberMovingBlocks;

	unsigned score;

	std::vector <std::shared_ptr<Block>> blocksMatrix;

	std::array <sf::Color, 3> colorsMatrix = { sf::Color::Green, sf::Color::Red, sf::Color::Yellow };

public:
	Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBricksInRow,
		unsigned numberBricksInColumn, float offsetHeight); //�����������
	~Field(void) {} //����������

	void GenerateField(void); //��������� ������

	float GetWidth(void); //������ ����
	std::vector <std::shared_ptr<Block>> GetBlocksMatrix(void); //������� ������

	void SetMovingBlock(void); //���������� ����������� ����� �� ����
	void SetBlockType(sf::Color& brickColor, int& brickHealth); //��������� ���� �����

	void MoveAllBlocks(void); //�������� ������
	void BlocksCollision(void); //���� ����������� ���������� �����
	bool CheckNewX(float posX, float posY); //�������� ������������ ���������� ������
	int DeleteBlock(unsigned number, float &bonusX, float &bonusY); //������� ����, ���� � ���� �� �������� ������

	bool EndGame(void); //����� ����

	void Draw(std::shared_ptr <sf::RenderWindow> window); //���������� ��� ����� �� ����
};