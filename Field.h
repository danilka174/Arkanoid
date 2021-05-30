#pragma once
#include <array>

#include "Block.h"

class Field { //класс игрового поля
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
		unsigned numberBricksInColumn, float offsetHeight); //конструктор
	~Field(void) {} //деструктор

	void GenerateField(void); //генерация блоков

	float GetWidth(void); //ширина поля
	std::vector <std::shared_ptr<Block>> GetBlocksMatrix(void); //матрица блоков

	void SetMovingBlock(void); //добавление движущегося блока на поле
	void SetBlockType(sf::Color& brickColor, int& brickHealth); //генерация типа блока

	void MoveAllBlocks(void); //движение блоков
	void BlocksCollision(void); //если столкнулись движущиеся блоки
	bool CheckNewX(float posX, float posY); //проверка правильности размещения блоков
	int DeleteBlock(unsigned number, float &bonusX, float &bonusY); //удалить блок, если у него не осталось жизней

	bool EndGame(void); //конец игры

	void Draw(std::shared_ptr <sf::RenderWindow> window); //нарисовать все блоки на поле
};