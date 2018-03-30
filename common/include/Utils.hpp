/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Utils.hpp
*/

#pragma once

#include <string>
#include <utility>

using Position = std::pair<size_t, size_t>;

enum Direction {
	NORTH,
	SOUTH,
	EST,
	WEST,
};

enum gameStatus {
	INGAME,
	WIN,
	LOSE,
	PAUSE,
};

struct Color {
	int r;
	int g;
	int b;
	int a;
};

struct Text {
	std::string text;
	Position pos;
	size_t size;
	Color color;
	std::string font;
};

struct Button {
	std::string text;
	std::string sprite;
	Position pos;
	bool active;
};

struct Disp {
	std::string path;
	char character;
	Position position;
};

static const size_t HEIGHT_BOARD = 5;
static const size_t WIDTH_BOARD = 5;