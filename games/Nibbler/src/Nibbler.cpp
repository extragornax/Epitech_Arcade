//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Nibbler.cpp
//

#include <iostream>
#include <vector>
#include <cstddef>
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
				sprites.push_back(SNAKE_HEAD_SPRITE);
				chars.push_back(SNAKE_HEAD_NORTH_CHAR);
				chars.push_back(SNAKE_HEAD_EAST_CHAR);
				chars.push_back(SNAKE_HEAD_WEST_CHAR);
				chars.push_back(SNAKE_HEAD_SOUTH_CHAR);
				_nibblerScene.getBoard().createTile(std::make_pair(i, j), sprites, chars, NORTH);
			} else if (str[j] == '2') {
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
	//updates board depending on the event we send (fct ptrs array?)
}

void	Nibbler::_spawnFood()
{
	
}

void	Nibbler::saveScore()
{

	//append score to a file
}

void	Nibbler::menuPause()
{
	//pause the game
}

bool	Nibbler::endGame()
{
	//check if game has ended yet
}

gameState	Nibbler::getStatus()
{
	//get gameState (ingame, paused, etc)
}
