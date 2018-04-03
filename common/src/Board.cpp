/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Board.cpp
*/

#include <iostream>
#include "Board.hpp"

void Board::Tile::setSprites(const std::vector<std::string> sprites)
{
	_sprites = sprites;
}

void Board::Tile::setCharacters(const std::vector<char> characteres)
{
	_characteres = characteres;
}

void Board::Tile::setDirection(const Direction direction)
{
	_direction = direction;
}

void Board::Tile::setColorBackground(const Color color)
{
	_background = color;
}

void Board::Tile::setColorForeground(const Color color)
{
	_foreground = color;
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

Color Board::Tile::getColorBackground() const
{
	return _background;
}

Color Board::Tile::getColorForeground() const
{
	return _foreground;
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

void Board::setColorBackground(const Position &pos, const Color color)
{
	return _board[pos.first][pos.second].setColorBackground(color);
}

void Board::setColorForeground(const Position &pos, const Color color)
{
	return _board[pos.first][pos.second].setColorForeground(color);
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

Color Board::getColorBackground(const Position &pos) const
{
	return _board[pos.first][pos.second].getColorBackground();
}

Color Board::getColorForeground(const Position &pos) const
{
	return _board[pos.first][pos.second].getColorForeground();
}

void Board::createTile(const Position &pos, const std::vector<std::string> sprites,
			const std::vector<char> characters, const Direction direction)
{
	_board[pos.first][pos.second].setSprites(sprites);
	_board[pos.first][pos.second].setCharacters(characters);
	_board[pos.first][pos.second].setDirection(direction);
}