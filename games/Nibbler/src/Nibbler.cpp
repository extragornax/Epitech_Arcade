//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Nibbler.cpp
//

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include <list>
#include "Define.hpp"
#include "IGame.hpp"
#include "Nibbler.hpp"
#include "Utils.hpp"

extern "C"
{
        IGame *createGame()
	{
		return new Nibbler;
	}
}

Nibbler::Nibbler()
{
	_setBoard();
	srand(time(NULL));
	_endgame = false;
	_score = 0;
	_gameStatus = INGAME;
	_spawnFood();
}

Nibbler::~Nibbler()
{
}

void	Nibbler::_setBoard()
{
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Color color;

	for (unsigned int i = 0; i < HEIGHT_BOARD; i++) {
		for (unsigned int j = 0; j < WIDTH_BOARD; j++) {
			if (baseMap[i][j] == '1') {
				sprites.push_back(WALL_SPRITE);
				chars.push_back(WALL_CHAR);
				_nibblerScene.getBoardGame().createTile(std::make_pair(i, j), sprites, chars, NORTH);
				color.r = 636;
				color.b = 31;
				color.g = 375;
				_nibblerScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
				color.r = 0;
				color.b = 0;
				color.g = 0;
				_nibblerScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
			} else if (baseMap[i][j] == '3') {
				_snake.push_front(std::make_pair(i, j));
				sprites.push_back(SNAKE_HEAD_SPRITE);
				chars.push_back(SNAKE_BODY_CHAR);
				_nibblerScene.getBoardGame().createTile(std::make_pair(i, j), sprites, chars, NORTH);
				color.r = 0;
				color.b = 0;
				color.g = 1000;
				_nibblerScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
				color.r = 1000;
				color.b = 0;
				color.g = 0;
				_nibblerScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
			} else if (baseMap[i][j] == '2') {
				_snake.push_back(std::make_pair(i, j));
				sprites.push_back(SNAKE_BODY_SPRITE);
				chars.push_back(SNAKE_BODY_CHAR);
				_nibblerScene.getBoardGame().createTile(std::make_pair(i, j), sprites, chars, NORTH);
				color.r = 0;
				color.b = 0;
				color.g = 1000;
				_nibblerScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
				color.r = 1000;
				color.b = 0;
				color.g = 0;
				_nibblerScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
			} else {
				sprites.push_back(BACKGROUND_SPRITE);
				chars.push_back(BACKGROUND_CHAR);
				_nibblerScene.getBoardGame().createTile(std::make_pair(i, j), sprites, chars, NORTH);
				color.r = 0;
				color.b = 0;
				color.g = 1000;
				_nibblerScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
				color.r = 0;
				color.b = 0;
				color.g = 1000;
				_nibblerScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
			}
			chars.clear();
			sprites.clear();
		}
	}
}

Scene	&Nibbler::updateScene(size_t event)
{
	_updateBoard(_nibblerScene.getBoardGame(), event);
	return (_nibblerScene);
}

void	Nibbler::_updateBoard(Board &board, size_t event)
{
	long unsigned int i = std::get<0> (_snake.front());
	long unsigned int j = std::get<1> (_snake.front());
	long unsigned int i2 = std::get<0> (_snake.back());
	long unsigned int j2 = std::get<1> (_snake.back());
	std::string eventStr = std::get<1> (DICO[event]);

	if (eventStr == "RIGHT") {
		_moveSideway(board, i, j, i2, j2, 1);
	} else if (eventStr == "LEFT") {
		_moveSideway(board, i, j, i2, j2, -1);
	} else if (eventStr == "UP") {
		_moveVertical(board, i, j, i2, j2, -1);
	} else if (eventStr == "DOWN") {
		_moveVertical(board, i, j, i2, j2, 1);
	} else if (eventStr == "NO_EVENT") {
		if (board.getDirection(_snake.front()) == WEST || board.getDirection(_snake.front()) == EAST) {
			_moveSideway(board, i, j, i2, j2, (board.getDirection(_snake.front()) == WEST) ? 1 : -1);
		} else {
			_moveVertical(board, i, j, i2, j2, (board.getDirection(_snake.front()) == SOUTH) ? 1 : -1);
		}
	}
}

void	Nibbler::_moveSideway(Board &board, long unsigned int i, long unsigned int j,
			       long unsigned int i2, long unsigned int j2, int incr)
{
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Direction direction = (incr == 1) ? WEST : EAST;
	// Recovers head and tail of the snake and the second node position
	Position pos_first = std::make_pair(i, j + incr);
	Position pos_last = std::make_pair(i2, j2);
	Position pos_second = *std::next(_snake.begin());
	Color color;

	if (j + incr < 20 && board.getCharacters(std::make_pair(i, j + incr))[0] == BACKGROUND_CHAR) {
		// Adds a new node to the list in front and removes one in the back, updating
		// the board at the same time.
		chars.push_back(SNAKE_BODY_CHAR);
		sprites.push_back(SNAKE_HEAD_SPRITE);
		_snake.push_front(pos_first);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		board.setColorBackground(pos_first, color);
		color.r = 1000;
		color.b = 0;
		color.g = 0;
		board.setColorForeground(pos_first, color);
		chars.clear();
		sprites.clear();
		chars.push_back(BACKGROUND_CHAR);
		sprites.push_back(BACKGROUND_SPRITE);
		board.setCharacters(pos_last, chars);
		board.setSprites(pos_last, sprites);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		_nibblerScene.getBoardGame().setColorBackground(pos_last, color);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		_nibblerScene.getBoardGame().setColorForeground(pos_last, color);
		_snake.pop_back();
	} else if (j + incr < 20 && board.getCharacters(std::make_pair(i, j + incr))[0] == FOOD_CHAR) {
		// Adds a new node to the front of the list, but doesnt remove one in the back
		// since we simply gained a node via eating.
		chars.push_back(SNAKE_BODY_CHAR);
		sprites.push_back(SNAKE_HEAD_SPRITE);
		_snake.push_front(pos_first);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		board.setColorBackground(pos_first, color);
		color.r = 1000;
		color.b = 0;
		color.g = 0;
		board.setColorForeground(pos_first, color);
		chars.clear();
		sprites.clear();
		_spawnFood();
	} else if (j + incr < 20 && pos_second == std::make_pair(i, j + incr)) {
		_moveSideway(board, i, j, i2, j2, -incr);
		// Means you're trying to go backwards, which you can't do in snake, so just does nothing.
		;
	} else {
		// If the tile on the direction you're trying to go to is neither food or empty,
		// means it's the snake itself or a wall, thus ending the game.
		_endgame = true;
	}
	chars.clear();
	sprites.clear();
	chars.push_back(SNAKE_BODY_CHAR);
	sprites.push_back(SNAKE_BODY_SPRITE);;
	board.setCharacters(std::make_pair(i, j), chars);
	board.setSprites(std::make_pair(i, j), sprites);
	color.r = 0;
	color.b = 0;
	color.g = 1000;
	board.setColorBackground(std::make_pair(i, j), color);
	color.r = 1000;
	color.b = 0;
	color.g = 0;
	board.setColorForeground(std::make_pair(i, j), color);
}

void	Nibbler::_moveVertical(Board &board, long unsigned int i, long unsigned int j,
			       long unsigned int i2, long unsigned int j2, int incr)
{
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Direction direction = (incr == 1) ? SOUTH : NORTH;
	// Recovers head and tail of the snake and the second node position
	Position pos_first = std::make_pair(i + incr, j);
	Position pos_last = std::make_pair(i2, j2);
	Position pos_second = *std::next(_snake.begin());
	Color color;

	if (i + incr < 20 && board.getCharacters(std::make_pair(i + incr, j))[0] == BACKGROUND_CHAR) {
		// Adds a new node to the list in front and removes one in the back, updating
		// the board at the same time.
		chars.push_back(SNAKE_BODY_CHAR);
		sprites.push_back(SNAKE_HEAD_SPRITE);
		_snake.push_front(pos_first);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		board.setColorBackground(pos_first, color);
		color.r = 1000;
		color.b = 0;
		color.g = 0;
		board.setColorForeground(pos_first, color);
		chars.clear();
		sprites.clear();
		chars.push_back(BACKGROUND_CHAR);
		sprites.push_back(BACKGROUND_SPRITE);
		board.setCharacters(pos_last, chars);
		board.setSprites(pos_last, sprites);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		board.setColorBackground(pos_last, color);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		board.setColorForeground(pos_last, color);
		_snake.pop_back();
	} else if (i + incr < 20 && board.getCharacters(std::make_pair(i + incr, j))[0] == FOOD_CHAR) {
		// Adds a new node to the front of the list, but doesnt remove one in the back
		// since we simply gained a node via eating.
		chars.push_back(SNAKE_BODY_CHAR);
		sprites.push_back(SNAKE_HEAD_SPRITE);
		_snake.push_front(pos_first);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		board.setColorBackground(pos_first, color);
		color.r = 1000;
		color.b = 0;
		color.g = 0;
		board.setColorForeground(pos_first, color);
		_spawnFood();
	} else if (i + incr < 20 && pos_second == std::make_pair(i + incr, j)) {
		_moveVertical(board, i, j, i2, j2, -incr);
		// Means you're trying to go backwards, which you can't do in snake, so just does nothing.
		;
	} else {
		// If the tile on the direction you're trying to go to is neither food or empty,
		// means it's the snake itself or a wall, thus ending the game.
		_gameStatus = LOSE;
		_endgame = true;
	}
	chars.clear();
	sprites.clear();
	chars.push_back(SNAKE_BODY_CHAR);
	sprites.push_back(SNAKE_BODY_SPRITE);;
	board.setCharacters(std::make_pair(i, j), chars);
	board.setSprites(std::make_pair(i, j), sprites);
	color.r = 0;
	color.b = 0;
	color.g = 1000;
	board.setColorBackground(std::make_pair(i, j), color);
	color.r = 1000;
	color.b = 0;
	color.g = 0;
	board.setColorForeground(std::make_pair(i, j), color);
}

void	Nibbler::_spawnFood()
{
	int i = rand() % 20;
	int j = rand() % 20;
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Color color;

	while (_nibblerScene.getBoardGame().getCharacters(std::make_pair(i, j))[0] != BACKGROUND_CHAR) {
		i = rand() % 20;
		j = rand() % 20;
	}
	chars.push_back(FOOD_CHAR);
	sprites.push_back(FOOD_SPRITE);
	_nibblerScene.getBoardGame().setCharacters(std::make_pair(i, j), chars);
	_nibblerScene.getBoardGame().setSprites(std::make_pair(i, j), sprites);
	color.r = 0;
	color.b = 0;
	color.g = 1000;
	_nibblerScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
	color.r = 1000;
	color.b = 0;
	color.g = 1000;
	_nibblerScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
}

void	Nibbler::saveScore(std::string nickname)
{
	//append score to a file, to be done later ?
	(void) nickname;
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

gameStatus	Nibbler::getStatus()
{
	//get gameState (ingame, paused, etc)
	return _gameStatus;
}
