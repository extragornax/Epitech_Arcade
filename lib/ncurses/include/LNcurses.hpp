//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ncurses header
//

#pragma once

#include <curses.h>
#include "ILib.hpp"

#define ESCAPE_KEY 27

class LNcurses : public ILib {
public:
	LNcurses();
	~LNcurses() override;
	void clear() override;
	void playSound(const std::string &path) override;
	void stopSound(const std::string &path) override;
	void drawText(Text &text) override;
	void drawDisp(Disp &disp) override;
	void drawButton(Button &button) override;
	void drawScene(Scene &scene) override;
	void display() override;
        size_t getKey() override;

private:
	void _moveCursor(Position pos);
	void _refreshScreen();
	void _print_text(std::string text);
	void _get_winSize();

private:
	char _getch;
	WINDOW *_window;
	Position _start_game;
	Position _screen_size;
};
