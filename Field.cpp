#include "Field.h"

#define CHANCE 15
#define CHANCE_OF_BONUS 40
#define MINUS_HEALTH -1

Field::Field(float fieldWindowHeight, float fieldWindowWidth, unsigned numberBlocksInRow, unsigned numberBlocksInColumn, float offsetHeight) { //конструктор
	height = fieldWindowHeight;
	width = fieldWindowWidth;
	blocksInRow = numberBlocksInRow;
	blocksInColumn = numberBlocksInColumn;
	offset = offsetHeight;
	numberMovingBlocks = 0;

	GenerateField();
}

void Field::GenerateField(void) { //генерация набора блоков
	float blockHeight = height / blocksInColumn;
	float blockWidth = width / blocksInRow;
	float posX = 0, posY = 0;
	sf::Color blockColor;
	int blockHealth;

	for (unsigned i = 0; i < blocksInColumn; i++)
		for (unsigned j = 0; j < blocksInRow; j++) {
			posX = j * blockWidth;
			posY = offset + i * blockHeight;
			SetBlockType(blockColor, blockHealth);
			blocksMatrix.push_back(std::make_shared<Block>(blockHeight, blockWidth, posX, posY, blockHealth, blockColor));
		}
}

float Field::GetWidth(void) { //ширина поля
	return width;
}

std::vector <std::shared_ptr<Block>> Field::GetBlocksMatrix(void) { //матрица блоков
	return blocksMatrix;
}

void Field::SetMovingBlock(void) { //добавление движущегося блока на поле
	float randomX;
	float y = offset + height * (float)1.03;
	float blockWidth = width / blocksInRow;
	float blockHeight = height / blocksInColumn;

	if (numberMovingBlocks < blocksInRow / 2) {
		do
			randomX = (float)(rand() % (int)(width - blockWidth));
		while (!CheckNewX(randomX, y));

		blocksMatrix.push_back(std::make_shared <MovingBlock>(blockHeight, blockWidth, randomX, y));
		numberMovingBlocks += 1;
	}
}

void Field::SetBlockType(sf::Color& blockColor, int& blockHealth) { //задать тип блока рандомно
	switch (rand() % CHANCE) {
	case 0: { //неразрушаемый красный блок
		blockColor = colorsMatrix[1];
		blockHealth = -1;
	}
			break;
	case 1: { //ускоряющий желтый блок
		blockColor = colorsMatrix[2];
		blockHealth = 1;
	}
			break;
	default: { //обычный блок
		blockColor = colorsMatrix[0];
		blockHealth = 1;
	}
			 break;
	}
}

void Field::MoveAllBlocks(void) { //движение блоков
	for (unsigned k = 0; k < blocksMatrix.size(); k++)
		blocksMatrix[k]->Move(width);
}

void Field::BlocksCollision(void) { //если столкнулись движущиеся блоки
	sf::Color brickColor1, brickColor2;
	float leftSide1, rightSide1, leftSide2, rightSide2;
	float speed;

	bool sameType, leftCollision, rightCollision;

	for (unsigned i = 0; i < blocksMatrix.size(); i++) {
		brickColor1 = blocksMatrix[i]->GetColor();
		leftSide1 = blocksMatrix[i]->GetPosX();
		rightSide1 = blocksMatrix[i]->GetPosX() + blocksMatrix[i]->GetWidth();
		speed = abs(blocksMatrix[i]->GetSpeedX());

		for (unsigned j = 0; j < blocksMatrix.size(); j++) {
			brickColor2 = blocksMatrix[j]->GetColor();
			leftSide2 = blocksMatrix[j]->GetPosX();
			rightSide2 = blocksMatrix[j]->GetPosX() + blocksMatrix[j]->GetWidth();

			sameType = (brickColor1 == sf::Color::Blue) && (brickColor2 == sf::Color::Blue);
			leftCollision = abs(leftSide1 - rightSide2) < speed;
			rightCollision = abs(rightSide1 - leftSide2) < speed;

			if ((i != j) && sameType && (leftCollision || rightCollision))
				blocksMatrix[i]->SetSpeedX(-1);
		}
	}
}

bool Field::CheckNewX(float posX, float posY) { //проверка правильности размещения блоков
	float leftBoarder, rightBoarder, brickOut, brickPosY;

	for (unsigned k = 0; k < blocksMatrix.size(); k++) {
		brickPosY = blocksMatrix[k]->GetPosY();
		leftBoarder = blocksMatrix[k]->GetPosX() - blocksMatrix[k]->GetWidth();
		rightBoarder = blocksMatrix[k]->GetPosX() + blocksMatrix[k]->GetWidth();
		brickOut = width - blocksMatrix[k]->GetWidth();

		if (brickPosY == posY)
			if (posX >= leftBoarder && posX <= rightBoarder || posX >= brickOut)
				return false;
	}

	return true;
}

int Field::DeleteBlock(unsigned number, float& bonusX, float& bonusY) { //удалить блок, если у него не осталось жизней
	blocksMatrix[number]->SetHealth(MINUS_HEALTH);

	if (blocksMatrix[number]->GetHealth() == 0) {
		if (rand() % 100 < CHANCE_OF_BONUS) {
			bonusX = blocksMatrix[number]->GetPosX() + blocksMatrix[number]->GetWidth() / 2;
			bonusY = blocksMatrix[number]->GetPosY() + blocksMatrix[number]->GetHeight();
		}

		if (blocksMatrix[number]->GetColor() == sf::Color::Blue)
			numberMovingBlocks -= 1;
		blocksMatrix.erase(blocksMatrix.begin() + number);
	}

	return 1;
}

bool Field::EndGame(void) { //конец игры
	for (unsigned k = 0; k < blocksMatrix.size(); k++)
		if (blocksMatrix[k]->GetColor() != sf::Color::Red)
			return false;
	return true;
}

void Field::Draw(std::shared_ptr <sf::RenderWindow> window) { //нарисовать все блоки на поле
	for (unsigned k = 0; k < blocksMatrix.size(); k++)
		blocksMatrix[k]->Draw(window);
}