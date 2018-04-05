//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Pacman.cpp
//

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include <list>
#include "DefinePacman.hpp"
#include "IGame.hpp"
#include "Pacman.hpp"
#include "Utils.hpp"

extern "C"
{
        IGame *create()
	{
		return new Pacman;
	}
}

Pacman::Pacman()
{
	_setBoard();
	srand(time(NULL));
	_endgame = false;
	_score = 0;
	_gameStatus = INGAME;
	_timeLimit = 270000; // to be severely reduced.
}

Pacman::~Pacman()
{
}

void	Pacman::_setBoard()
{
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Color color;
	int ghostCount = 0;
	Ghost	ghost;

	for (unsigned int i = 0; i < HEIGHT_BOARD; i++) {
		for (unsigned int j = 0; j < WIDTH_BOARD; j++) {
			if (baseMap[i][j] == '1') {
				sprites.push_back(WALL_SPRITE);
				chars.push_back(WALL_CHAR);
				_pacmanScene.getBoardGame().createTile(std::make_pair(i, j), sprites, chars, NORTH);
				color.r = 636;
				color.b = 31;
				color.g = 375;
				_pacmanScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
				color.r = 0;
				color.b = 0;
				color.g = 0;
				_pacmanScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
			} else if (baseMap[i][j] == '3') {
				_pacman = std::make_pair(i, j);
				sprites.push_back(PACMAN_SPRITE);
				chars.push_back(PACMAN_CHAR);
				_pacmanScene.getBoardGame().createTile(std::make_pair(i, j), sprites, chars, NORTH);
				color.r = 0;
				color.b = 0;
				color.g = 1000;
				_pacmanScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
				color.r = 1000;
				color.b = 0;
				color.g = 0;
				_pacmanScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
			} else if (baseMap[i][j] == '2') {
//				std::cout << "ghostcount : " << ghostCount<< std::endl;
				ghost.pos = std::make_pair(i, j);
				_ghosts.push_back(ghost);
				sprites.push_back(GHOST_SPRITE[ghostCount]);
				chars.push_back(GHOST_CHAR);
				ghostCount += 1;
				_pacmanScene.getBoardGame().createTile(std::make_pair(i, j), sprites, chars, NORTH);
				color.r = 0;
				color.b = 0;
				color.g = 1000;
				_pacmanScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
				color.r = 1000;
				color.b = 0;
				color.g = 0;
				_pacmanScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
			} else {
				sprites.push_back(FOOD_SPRITE);
				chars.push_back(FOOD_CHAR);
				_pacmanScene.getBoardGame().createTile(std::make_pair(i, j), sprites, chars, NORTH);
				color.r = 0;
				color.b = 0;
				color.g = 1000;
				_pacmanScene.getBoardGame().setColorBackground(std::make_pair(i, j), color);
				color.r = 0;
				color.b = 0;
				color.g = 1000;
				_pacmanScene.getBoardGame().setColorForeground(std::make_pair(i, j), color);
				++_foodCounter;
			}
			chars.clear();
			sprites.clear();
		}
	}
}

Scene	&Pacman::updateScene(size_t event)
{
	static std::clock_t	startTime = std::clock();
	static size_t	tryEvent = 0;
	static int beforeGhosts = 0;

	if (event != 0)
		tryEvent = event;
	if (std::clock() - startTime > _timeLimit) {
/*		if (beforeGhosts >= 7) {
			_updateGhosts(_pacmanScene.getBoardGame(), 0);
			if (beforeGhosts >= 8)
				_updateGhosts(_pacmanScene.getBoardGame(), 1);
			if (beforeGhosts >= 9)
				_updateGhosts(_pacmanScene.getBoardGame(), 2);
			if (beforeGhosts >= 10)
				_updateGhosts(_pacmanScene.getBoardGame(), 3);
		}
		if (_endgame)
		return _pacmanScene;*/
		_updateBoard(_pacmanScene.getBoardGame(), tryEvent);
		startTime = std::clock();
		tryEvent = 0;
		++beforeGhosts;
	}
	return (_pacmanScene);
}

void	Pacman::_updateGhosts(Board &board, int idx)
{
	int	i = std::get<0> (_ghosts[idx].pos);
	int	j = std::get<1> (_ghosts[idx].pos);
	bool	done = false;
	std::vector<char>	chars;
	std::vector<std::string>	sprites;
	Direction direction = NORTH;
	int	rdm = rand() % 4;
	int	i2 = i;
	int	j2 = j;
	Ghost	ghost;

	if (i == 11 && j >= 8 && j <= 11) {
		if (board.getCharacters(std::make_pair(9, 9))[0] == PACMAN_CHAR) {
			_endgame = true;
			return;
		}
		chars = board.getCharacters(std::make_pair(i, j));
		sprites = board.getSprites(std::make_pair(i, j));
		ghost.sprites = sprites;
		ghost.chars = chars;
		ghost.pos = std::make_pair(9, 9);
		_ghosts[idx] = ghost;
	} else {
		while (!done)
			switch (rdm) {
			case 0:
				i2 -= 1;
				direction = WEST;
				break;
			case 1:
				i2 += 1;
				direction = EAST;
				break;
			case 2:
				j2 -= 1;
				direction = NORTH;
				break;
			case 3:
				j2 += 1;
				direction = SOUTH;
				break;
			}
	}
	if (board.getCharacters(std::make_pair(i2, j2))[0] != WALL_CHAR
	    && board.getCharacters(std::make_pair(i2, j2))[0] != GHOST_CHAR) {
		if (board.getCharacters(std::make_pair(i2, j2))[0] == PACMAN_CHAR)
			_endgame = true;
		board.setCharacters(_ghosts[idx].pos, _ghosts[idx].chars);
		board.setSprites(_ghosts[idx].pos, _ghosts[idx].sprites);
		ghost.pos = std::make_pair(i2, j2);
		chars.push_back(GHOST_CHAR);
		sprites.push_back(GHOST_SPRITE[idx]);
		ghost.chars = board.getCharacters(std::make_pair(i2, j2));
		ghost.sprites = board.getSprites(std::make_pair(i2, j2));
		board.setCharacters(std::make_pair(i2, j2), chars);
		board.setSprites(std::make_pair(i2, j2), sprites);
		board.setDirection(std::make_pair(i2, j2), direction);
		_ghosts[idx] = ghost;
	}
}

void	Pacman::_updateBoard(Board &board, size_t event)
{
	long unsigned int i = std::get<0> (_pacman);
	long unsigned int j = std::get<1> (_pacman);
	std::string eventStr = std::get<1> (DICO[event]);

	if (eventStr == "RIGHT") {
		_moveSideway(board, (int) i, (int) j, 1);
	} else if (eventStr == "LEFT") {
		_moveSideway(board, (int) i, (int) j, -1);
	} else if (eventStr == "UP") {
		_moveVertical(board, (int) i, (int) j, -1);
	} else if (eventStr == "DOWN") {
		_moveVertical(board, (int) i, (int) j, 1);
	} else if (eventStr == "NO_EVENT") {
		if (board.getDirection(_pacman) == WEST || board.getDirection(_pacman) == EAST) {
			_moveSideway(board, (int) i, (int) j, (board.getDirection(_pacman) == WEST) ? 1 : -1);
		}
		else {
			_moveVertical(board, (int) i, (int) j, (board.getDirection(_pacman) == SOUTH) ? 1 : -1);
		}
	}
}

void	Pacman::_moveSideway(Board &board, int i, int j,
			     int incr)
{
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Direction direction = (incr == 1) ? WEST : EAST;
	// Recovers pacman position
	Position pos_first = std::make_pair(i, j + incr);
	Position pos_last = _pacman;
	Color color;

//	std::cout <<"Atleast i'm in the correct function" << std::endl;
	if (j + incr > 0 && j + incr < 20 && board.getCharacters(std::make_pair(i, j + incr))[0] == BACKGROUND_CHAR) {
		// Moves pacman to the next position, TODO : switch sprites depending
		// on wether he is mouth opened or not;
		chars.push_back(PACMAN_CHAR);
		sprites.push_back(PACMAN_SPRITE);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		_pacman = pos_first;
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
		_pacmanScene.getBoardGame().setColorBackground(pos_last, color);
		color.r = 0;
		color.b = 0;
		color.g = 1000;
		_pacmanScene.getBoardGame().setColorForeground(pos_last, color);
	} else if (j + incr > 0 && j + incr < 20 && board.getCharacters(std::make_pair(i, j + incr))[0] == FOOD_CHAR) {
		// Eats pacgum and increase score
		chars.push_back(PACMAN_CHAR);
		sprites.push_back(PACMAN_SPRITE);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		_pacman = pos_first;
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
		_pacmanScene.getScore() += 1;
		--_foodCounter;
//		if (_pacmanScene.getScore() % 3 == 0)
//			_timeLimit -= 10000;
	} else if ((j + incr == -1 || j + incr == 20)) {
//		   && board.getCharacters(std::make_pair(i, j + incr))[0] == BACKGROUND_CHAR) {
		// If you happen to be able to go out of bounds of the map, means you should be teleported to the
		// other side
//		std::cout << "je suis la" << std::endl;
		_pacman = (j + incr == -1) ? std::make_pair(i, 19) : std::make_pair(i, 0);
		chars.push_back(PACMAN_CHAR);
		sprites.push_back(PACMAN_SPRITE);
		board.setCharacters(_pacman, chars);
		board.setSprites(_pacman, sprites);
		board.setDirection(_pacman, direction);
		chars.clear();
		sprites.clear();
		chars.push_back(BACKGROUND_CHAR);
		sprites.push_back(BACKGROUND_SPRITE);
		board.setCharacters(pos_last, chars);
		board.setSprites(pos_last, sprites);
	} else if (j + incr < 20 && board.getCharacters(std::make_pair(i, j + incr))[0] == GHOST_CHAR) {
		// If the tile on the direction you're trying to go to is a ghost, you lose
		_endgame = true;
	} else if (j + incr >= 0 && j + incr <= 20 && board.getCharacters(std::make_pair(i, j + incr))[0] == WALL_CHAR) {
		switch (board.getDirection(_pacman)) {
		case WEST:
			if (board.getCharacters(std::make_pair(i, j + 1))[0] == WALL_CHAR)
				return;
			break;
		case EAST:
			if (board.getCharacters(std::make_pair(i, j - 1))[0] == WALL_CHAR)
				return;
			break;
		case NORTH:
			if (board.getCharacters(std::make_pair(i - 1, j))[0] == WALL_CHAR)
				return;
			break;
		case SOUTH:
			if (board.getCharacters(std::make_pair(i + 1, j))[0] == WALL_CHAR)
				return;
			break;
		}		
		if (board.getDirection(_pacman) == WEST || board.getDirection(_pacman) == EAST) {
			_moveSideway(board, (int) i, (int) j, (board.getDirection(_pacman) == WEST) ? 1 : -1);
		}
		else {
			_moveVertical(board, (int) i, (int) j, (board.getDirection(_pacman) == SOUTH) ? 1 : -1);
		}
	}
}

void	Pacman::_moveVertical(Board &board, int i, int j,
			      int incr)
{
	std::vector<std::string> sprites;
	std::vector<char> chars;
	Direction direction = (incr == 1) ? SOUTH : NORTH;
	// Recovers head and tail of the snake and the second node position
	Position pos_first = std::make_pair(i + incr, j);
	Position pos_last = _pacman;
	Color color;

	if (i + incr < 20 && board.getCharacters(std::make_pair(i + incr, j))[0] == BACKGROUND_CHAR) {
		// Moves pacman to the next position, TODO : switch sprites depending
		// on wether he is mouth opened or not;
		chars.push_back(PACMAN_CHAR);
		sprites.push_back(PACMAN_SPRITE);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		_pacman = pos_first;
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
	} else if (i + incr < 20 && board.getCharacters(std::make_pair(i + incr, j))[0] == FOOD_CHAR) {
		// Adds a new node to the front of the list, but doesnt remove one in the back
		// since we simply gained a node via eating.
		chars.push_back(PACMAN_CHAR);
		sprites.push_back(PACMAN_SPRITE);
		board.setCharacters(pos_first, chars);
		board.setSprites(pos_first, sprites);
		board.setDirection(pos_first, direction);
		_pacman = pos_first;
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
		_pacmanScene.getScore() += 1;
		--_foodCounter;
//		if (_pacmanScene.getScore() % 3 == 0)
//			_timeLimit -= 10000;
	}  else if (i + incr < 20 && board.getCharacters(std::make_pair(i + incr, j))[0] == GHOST_CHAR) {
		// If the tile on the direction you're trying to go to is a ghost, you lose the game
		_gameStatus = LOSE;
		_endgame = true;
	} else if (i + incr <= 20 && board.getCharacters(std::make_pair(i + incr, j))[0] == WALL_CHAR) {
		switch (board.getDirection(_pacman)) {
		case WEST:
			if (board.getCharacters(std::make_pair(i, j + 1))[0] == WALL_CHAR)
				return;
			break;
		case EAST:
			if (board.getCharacters(std::make_pair(i, j - 1))[0] == WALL_CHAR)
				return;
			break;
		case NORTH:
			if (board.getCharacters(std::make_pair(i - 1, j))[0] == WALL_CHAR)
				return;
			break;
		case SOUTH:
			if (board.getCharacters(std::make_pair(i + 1, j))[0] == WALL_CHAR)
				return;
			break;
		}
		if (board.getDirection(_pacman) == WEST || board.getDirection(_pacman) == EAST) {
			_moveSideway(board, (int) i, (int) j, (board.getDirection(_pacman) == WEST) ? 1 : -1);
		}
		else {
			_moveVertical(board, (int) i, (int) j, (board.getDirection(_pacman) == SOUTH) ? 1 : -1);
		}
	}
}

void	Pacman::saveScore(std::string nickname)
{
	//append score to a file, to be done later ?
	(void) nickname;
}

void	Pacman::menuPause()
{
	//pauses the game (popup?)
	_gameStatus = PAUSE;
}

bool	Pacman::endGame()
{
	if (_foodCounter == 0)
		_endgame = true;
	return _endgame;
}

gameStatus	Pacman::getStatus()
{
	//get gameState (ingame, paused, etc)
	return _gameStatus;
}
