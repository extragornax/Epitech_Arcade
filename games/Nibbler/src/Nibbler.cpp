//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Nibbler.cpp
//

#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include "Define.hpp"
#include "Nibbler.hpp"
#include "IGame.hpp"

extern "C"
{
	std::unique_ptr<IGame> createGame()
	{
		return std::make_unique(new Nibbler());
	}
}

Nibbler::Nibbler() : _nibblerScene()
{
	_setBoard();
	srand(time(NULL));
	_endgame = false;
	_score = 0;
	_gameStatus = INGAME;
}

~Nibbler::Nibbler()
{

}

void	&Nibbler::_setBoard()
{
	std::fstream fs;
	char str[20];

	fs.open(NIBBLER_CONF, ios_base::in);
	for (int i = 0; i < 20; i++) {
		fs.getline(str, 20);
		for (int j = 0; j < 20; j++) {
			std::vector<std::string> sprites;
			std::vector<char> chars;
			if (str[j] == '1') {
				sprites.push_back(WALL_SPRITE);
				chars.push_back(WALL_CHAR);
				_nibblerScene.getBoard().createTile(std::make_pair(i, j), sprites, chars, NORTH);
			} else if (str[j] == '3') {
				_snake.push_front(std::make_pair(i, j));
				sprites.push_back(SNAKE_BODY_SPRITE);
				chars.push_back(SNAKE_BODY_CHAR);
				_nibblerScene.getBoard().createTile(std::make_pair(i, j), sprites, chars, NORTH);
			} else if (str[j] == '2') {
				_snake.push_back(std::make_pair(i, j));
				sprites.push_back(SNAKE_BODY_SPRITE);
				chars.push_back(SNAKE_BODY_CHAR);
				_nibblerScene.getBoard().createTile(std::make_pair(i, j), sprites, chars, NORTH);
			} else {
				sprites.push_back(BACKGROUND_SPRITE);
				chars.push_back(BACKGROUND_CHAR);
				_nibblerScene.getBoard().createTile(std::make_pair(i, j), sprites, chars, NORTH);
			}
		}
	}
}

Scene	&Nibbler::updateScene(std::string event)
{
	_updateBoard(_nibblerScene.getBoard(), event);
	return (_nibblerScene);
}

void	Nibbler::_upadeBoard(Board &board)
{
	int i = std::get<0> (_snake.front());
	int j = std::get<1> (_snake.front());
	int i2 = std::get<0> (_snake.back());
	int j2 = std::get<1> (_snake.back());

	if (event == "KeyRight") {
		_moveSideway(board, i, j, i2, j2, 1);
	} else if (event == "KeyLeft") {
		_moveSideway(board, i, j, i2, j2, -1);
	} else if (event == "KeyUp") {
		_moveVertical(board, i, j, i2, j2, -1);
	} else if (event == "KeyDown") {
		_moveVertical(board, i, j, i2, j2, 1);
	} else if (event == "") {
		if (board.getDirection(_snake.front()) == WEST || board.getDirection(_snake.front()) == EAST) {
			_moveSideway(board, i, j, i2, j2, (board.getDirection(_snake.front()) == WEST) ? 1 : -1);
		} else {
			_moveSideway(board, i, j, i2, j2, (board.getDirection(_snake.front()) == SOUTH) ? 1 : -1);
		}
	}
}

void	Nibbler::_moveVertical(Board &board, int i, int j, int i2, int j2, int incr)
{
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Direction direction = (incr == 1) ? SOUTH : NORTH;
	// Recovers head and tail of the snake and the second node position
	Position pos_first = std::make_pair(i, j + incr);
	Position pos_last = std::make_pair(i2, j2);
	Position pos_second = _snake.begin().next();

	if (j + incr < 20 && j + incr >= 0 && board.getCharacters(std::make_pair(i, j + incr)) == BACKGROUND_CHAR) {
		// Adds a new node to the list in front and removes one in the back, updating
		// the board at the same time.
		chars.push_back(SNAKE_BODY_CHAR);
		sprites.push_back(SNAKE_BODY_SPRITE);
		_snake.push_front(pos_first);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		chars.clear();
		sprites.clear();
		chars.push_back(BACKGROUND_CHAR);
		sprites.push_back(BACKGROUND_SPRITE);
		board.setCharacters(pos_last, chars);
		board.setSprites(pos_last, sprites);
		_snake.pop_back();
	} else if (j + incr < 20 && j + incr >= 0 && board.getCharacters(std::make_pair(i, j + incr)) == FOOD_CHAR) {
		// Adds a new node to the front of the list, but doesnt remove one in the back
		// since we simply gained a node via eating.
		chars.push_back(SNAKE_BODY_CHAR);
		sprites.push_back(SNAKE_BODY_SPRITE);
		_snake.push_front(pos_first);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
	} else if (j + incr < 20 && j + incr >= 0 && pos_second == std::make_pair(i, j + incr)) {
		// Means you're trying to go backwards, which you can't do in snake, so just does nothing.
		;
	} else {
		// If the tile on the direction you're trying to go to is neither food or empty,
		// means it's the snake itself or a wall, thus ending the game.
		_endgame = true;
	}
}

void	Nibbler::_moveSideway(Board &board, int i, int j, int i2, int j2, int incr)
{
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Direction direction = (incr == 1) ? WEST : EAST;
	// Recovers head and tail of the snake and the second node position
	Position pos_first = std::make_pair(i + incr, j);
	Position pos_last = std::make_pair(i2, j2);
	Position pos_second = _snake.begin().next();

	if (i + incr < 20 && i + incr >= 0 && board.getCharacters(std::make_pair(i + incr, j)) == BACKGROUND_CHAR) {
		// Adds a new node to the list in front and removes one in the back, updating
		// the board at the same time.
		chars.push_back(SNAKE_BODY_CHAR);
		sprites.push_back(SNAKE_BODY_SPRITE);
		_snake.push_front(pos_first);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		chars.clear();
		sprites.clear();
		chars.push_back(BACKGROUND_CHAR);
		sprites.push_back(BACKGROUND_SPRITE);
		board.setCharacters(pos_last, chars);
		board.setSprites(pos_last, sprites);
		_snake.pop_back();
	} else if (i + incr < 20 && i + incr >= 0 && board.getCharacters(std::make_pair(i + incr, j)) == FOOD_CHAR) {
		// Adds a new node to the front of the list, but doesnt remove one in the back
		// since we simply gained a node via eating.
		chars.push_back(SNAKE_BODY_CHAR);
		sprites.push_back(SNAKE_BODY_SPRITE);
		_snake.push_front(pos_first);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
	} else if (i + incr < 20 && i + incr >= 0 && pos_second == std::make_pair(i + incr, j)) {
		// Means you're trying to go backwards, which you can't do in snake, so just does nothing.
		;
	} else {
		// If the tile on the direction you're trying to go to is neither food or empty,
		// means it's the snake itself or a wall, thus ending the game.
		_gameStatus = LOSE;
		_endgame = true;
	}
}

void	Nibbler::_spawnFood()
{
	int i = rand() % 20;
	int j = rand() % 20;
	std::vector<std::string> sprites;
	std::vector<char> chars;

	while (_nibblerScene.getBoard().getCharacters(std::make_pair(i, j))[0] != BACKGROUND_SPRITE) {
		i = rand() % 20;
		j = rand() % 20;
	}
	chars.push_back(FOOD_CHAR);
	sprites.push_back(FOOD_SPRITE);
	_nibblerScene.getBoard().setCharacters(std::make_pair(i, j), chars);
	_nibblerScene.getBoard().setSprites(std::make_pair(i, j), sprites);
}

void	Nibbler::saveScore(std::string nickname)
{
	//append score to a file, to be done later ?
}

void	Nibbler::menuPause()
{
	//pauses the game (popup?)
	_gameStatus = PAUSE;
}

bool	Nibbler::endGame()
{
	return _endgame;
}

gameState	Nibbler::getStatus()
{
	//get gameState (ingame, paused, etc)
	return _gameStatus;
}
