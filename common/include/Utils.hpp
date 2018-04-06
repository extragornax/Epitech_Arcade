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

/*
1 -> 4: ARROW_DIRECTION
5: ESCAPE
6: F12
7: BACKSPACE
8: KEY_R
9: HOME
10: END
11: PAGE_DOWN
12: PAGE_UP
13: VALIDATE
*/

static const std::vector<std::pair<size_t, std::string>> DICO =
		{{0, "NO_EVENT"},
		{1, "LEFT"}, {2, "RIGHT"}, {3, "UP"}, {4, "DOWN"},
		{5, "PAUSE"}, {6, "EXIT"}, {7, "BACK_MENU"}, {8, "RELOAD_GAME"},
		{9, "PREV_LIB"}, {10, "NEXT_LIB"}, {11, "PREV_GAME"}, {12, "NEXT_GAME"},
		{13, "VALIDATE"}};

enum Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST,
};

enum gameStatus {
	INGAME,
	WIN,
	LOSE,
	PAUSE,
	QUIT,
	MENU,
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
	Position pos;
};

static const size_t HEIGHT_BOARD = 20;
static const size_t WIDTH_BOARD = 20;
