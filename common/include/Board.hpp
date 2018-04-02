/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Board.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <array>
#include "Utils.hpp"

class Board {
public:
	Board();// = default;
	~Board() = default;

public:
	class Tile {
	public:
		Tile() = default;
		~Tile() = default;

	public:
		void setSprites(const std::vector<std::string>);
		void setCharacters(const std::vector<char>);
		void setDirection(const Direction);

	public:
		std::vector<std::string> getSprites() const;
		std::vector<char> getCharacters() const;
		Direction getDirection() const;

	private:
		std::vector<std::string> _sprites;
		std::vector<char> _characteres;
		Direction _direction;
	};

public:
	void setSprites(const Position &, const std::vector<std::string>);
	void setCharacters(const Position &, const std::vector<char>);
	void setDirection(const Position &, const Direction);

public:
	std::vector<std::string> getSprites(const Position &) const;
	std::vector<char> getCharacters(const Position &) const;
	Direction getDirection(const Position &) const;

public:
	void createTile(const Position &, const std::vector<std::string>,
			const std::vector<char>, const Direction);

private:
	std::vector<std::vector<Board::Tile>> _board;
};
