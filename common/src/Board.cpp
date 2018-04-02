/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Board.cpp
*/

#include <iostream>
#include "Board.hpp"
#include "Utils.hpp"

Board::Board()
{
	std::vector<Tile>  lines;

	lines.resize(WIDTH_BOARD);
	for (unsigned int i = 0; i < HEIGHT_BOARD; i++) {
		_board.push_back(lines);
	}
}

void Board::Tile::setSprites(const std::vector<std::string> sprites)
{
	std::cout << "checking the content of <sprites> : " << sprites[0] << std::endl;
	_sprites = sprites;
}

void Board::Tile::setCharacters(const std::vector<char> characteres)
{
	std::cout << "checking the content of <chars> : " << characteres[0] << std::endl;
	_characteres = characteres;
}

void Board::Tile::setDirection(const Direction direction)
{
	_direction = direction;
}

std::vector<std::string> Board::Tile::getSprites() const
{
	return _sprites;
}

std::vector<char> Board::Tile::getCharacters() const
{
	return _characteres;
}

Direction Board::Tile::getDirection() const
{
	return _direction;
}

void Board::setSprites(const Position &pos, const std::vector<std::string> sprites)
{
	_board[pos.first][pos.second].setSprites(sprites);
}

void Board::setCharacters(const Position &pos, const std::vector<char> characteres)
{
	_board[pos.first][pos.second].setCharacters(characteres);
}

void Board::setDirection(const Position &pos, const Direction direction)
{
	_board[pos.first][pos.second].setDirection(direction);
}

std::vector<std::string> Board::getSprites(const Position &pos) const
{
	return _board[pos.first][pos.second].getSprites();
}

std::vector<char> Board::getCharacters(const Position &pos) const
{
	return _board[pos.first][pos.second].getCharacters();
}

Direction Board::getDirection(const Position &pos) const
{
	return _board[pos.first][pos.second].getDirection();
}

void Board::createTile(const Position &pos, const std::vector<std::string> sprites,
			const std::vector<char> characters, const Direction direction)
{
	std::cout << "Creating tile at " << pos.first << ":" << pos.second << std::endl;
	_board[pos.first][pos.second].setSprites(sprites);
	_board[pos.first][pos.second].setCharacters(characters);
	_board[pos.first][pos.second].setDirection(direction);
	std::cout << "Done creating tile !" << std::endl;
}
