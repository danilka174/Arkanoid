#include "GameLoop.h"
#include "Parameters.h"

#define WIN_SCORE 25

GameLoop::GameLoop(void) { //конструктор
	score = 0;

	window = std::make_shared<sf::RenderWindow>(sf::VideoMode((unsigned)USER_WINDOW_WIDTH, (unsigned)USER_WINDOW_HEIGHT), "Arkanoid");
	window->setFramerateLimit(FRAME_RATE);

	field = std::make_shared<Field>(FIELD_WINDOW_HEIGHT, FIELD_WINDOW_WIDTH, NUMBER_BLOCKS_IN_ROW, NUMBER_BLOCKS_IN_COLUMN, OFFSET_HEIGHT);
	plate = std::make_shared <Plate>(PLATE_HEIGHT, PLATE_WIDTH, PLATE_X, PLATE_Y);
	ball = std::make_shared <Ball>(BALL_RADIUS, BALL_X, BALL_Y);
}

void GameLoop::Start(void) { //главный игровой цикл
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();

		AllMovement();
		AllColisions();
		BonusesWork();
		AllDrawing();
		End();
		window->display();
	}
}

void GameLoop::AllMovement(void) { //все движения
	plate->Move(USER_WINDOW_WIDTH);
	field->MoveAllBlocks();
	ball->Move(plate, USER_WINDOW_WIDTH);
}

void GameLoop::AllColisions(void) { //все столкновения
	score += ball->BallOut(USER_WINDOW_HEIGHT, plate);
	ball->CollisionWithWindow(USER_WINDOW_WIDTH, OFFSET_HEIGHT);
	StickingWork();
	CollisionWithBlocks();
	field->BlocksCollision();
}

void GameLoop::AllDrawing(void) { //нарисовать все игровые элементы
	field->Draw(window);
	ball->Draw(window);
	plate->Draw(window);
	CreateText();
}

void GameLoop::CollisionWithBlocks(void) { //обработка всех столкновений
	std::vector <std::shared_ptr<Block>> blocksMatrix = field->GetBlocksMatrix();
	float blockHeight, blockWidth, blockPosX, blockPosY;
	sf::Color blockColor;

	for (unsigned k = 0; k < blocksMatrix.size(); k++) {
		blockHeight = blocksMatrix[k]->GetHeight();
		blockWidth = blocksMatrix[k]->GetWidth();
		blockPosX = blocksMatrix[k]->GetPosX();
		blockPosY = blocksMatrix[k]->GetPosY();
		blockColor = blocksMatrix[k]->GetColor();

		if (ball->CollisionWithBlck(blockHeight, blockWidth, blockPosX, blockPosY) == 1) {
			float bonusX = 0, bonusY = 0;

			if (blockColor == sf::Color::Yellow)
				ball->SetSpeed(INCREASE_SPEED, INCREASE_SPEED);

			score += field->DeleteBlock(k, bonusX, bonusY);

			if (bonusX != 0 && bonusY != 0)
				ChooseBonus(bonusX, bonusY);
			break;
		}
	}
}

void GameLoop::ChooseBonus(float bonusX, float bonusY) { //выбор бонуса
	switch (rand() % BONUS_NUMBER) {
	case 0:
		bonusesMatrix.push_back(std::make_shared<ChangePlate>(bonusX, bonusY));
		break;
	case 1:
		bonusesMatrix.push_back(std::make_shared<ChangeBall>(bonusX, bonusY));
		break;
	case 2:
		bonusesMatrix.push_back(std::make_shared<BallStick>(bonusX, bonusY));
		break;
	case 3:
		bonusesMatrix.push_back(std::make_shared<BallBottom>(bonusX, bonusY));
		break;
	case 4:
		bonusesMatrix.push_back(std::make_shared<RandomPath>(bonusX, bonusY));
		break;
	case 5:
		bonusesMatrix.push_back(std::make_shared<MovingBlockBonus>(bonusX, bonusY));
		break;
	}
}

void GameLoop::StickingWork(void) { //прилипание мяча к платформе
	if (ball->CollisionWithBlck(plate->GetHeight(), plate->GetWidth(), plate->GetPosX(), plate->GetPosY(), plate->GetBallStick()) == 2) {
		plate->SetBallStick(-1);
		ball->SetBarOffset(ball->GetPosX() - plate->GetPosX());
	}
}

void GameLoop::BonusesWork(void) { //работа бонусов
	for (unsigned k = 0; k < bonusesMatrix.size(); k++) {
		bonusesMatrix[k]->Draw(window);
		if (bonusesMatrix[k]->Move(USER_WINDOW_HEIGHT, plate, ball, field)) {
			bonusesMatrix.erase(bonusesMatrix.begin() + k);
			break;
		}
	}
}

void GameLoop::CreateText(void) { //счет игры
	sf::Font font;
	font.loadFromFile("Textures/font.otf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize((unsigned)TEXT_SIZE);
	text.setPosition(TEXT_X, TEXT_Y);
	text.setString("Your score: " + std::to_string(score));

	window->draw(text);
}

void GameLoop::End(void) { //конец игры
	if (field->EndGame()) {
		sf::Texture texture;
		if (score >= WIN_SCORE)
			texture.loadFromFile("Textures/win.png");
		else
			texture.loadFromFile("Textures/lose.png");

		sf::RectangleShape shape(sf::Vector2f(USER_WINDOW_WIDTH, FIELD_WINDOW_HEIGHT));
		shape.setPosition(0, OFFSET_HEIGHT);
		shape.setTexture(&texture);

		window->draw(shape);
		window->display();

		sf::Clock timer;
		while (timer.getElapsedTime().asSeconds() < 3);

		window->close();
	}
}