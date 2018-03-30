//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ncurses constructor
//

#include <cstddef>
#include <iostream>
#include <curses.h>
#include "Board.hpp"
#include "Utils.hpp"
#include "LNcurses.hpp"
#include "Errors.hpp"

LNcurses::LNcurses()
	: _window(nullptr)
{
	createWindow();
}

LNcurses::~LNcurses()
{
	destroyWindow();
}

bool    LNcurses::createWindow()
{
	if ((_window = initscr()) == nullptr
	|| (raw() == ERR)
	|| (noecho()) == ERR
	|| (keypad(stdscr, 1)) == ERR
	|| atexit(LNcurses::destroyWindow) != 0)
		throw new GraphicalInitError("Error in Ncurses init\n");

}

void    LNcurses::destroyWindow()
{
	if ((endwin()) == ERR)
		throw new GraphicalCleanupError("Error on Ncurses exit\n");
}

void	LNcurses::clear()
{
	if ((wclear(_window)) == ERR
	|| (wnoutrefresh(_window)) == ERR
	|| (wrefresh(_window)) == ERR)
		throw new GraphicalInLibError("Error in screen clear Ncurses\n");
}

char	LNcurses::getKey()
{
	char ret;

	if ((ret = getch()) == ERR)
		throw new GraphicalInLibError("Error in retrieving user input key\n");
	return ret;
}

void    LNcurses::drawText(Text &text)
{
	moveCursor(text.Position);
	print_text(text.text);
	refreshScreen();
}

void    LNcurses::moveCursor(Position pos)
{
	if ((move((int) pos[0], (int) pos[1])) == ERR)
		throw new GraphicalInLibError("Error in moving the pointer to print in Ncurses\n");
}

void    LNcurses::refreshScreen()
{
	if ((refresh()) == ERR)
		throw new GraphicalInLibError("Error in refreshing Ncurses\n");
}

void    LNcurses::print_text(std::string text)
{
	if ((printw("%s", text.c_str())) == ERR)
		throw new GraphicalInLibError("Error in printing in Ncurses\n");
}