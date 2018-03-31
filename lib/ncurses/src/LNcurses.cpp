//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ncurses constructor
//

#include <cstddef>
#include <iostream>
#include <string>
#include <string.h>
#include <curses.h>
#include "Board.hpp"
#include "Utils.hpp"
#include "LNcurses.hpp"
#include "Errors.hpp"

LNcurses::LNcurses()
	: _window(nullptr),
	_start_game_x(0),
	_start_game_y(0)
{
	if ((_window = initscr()) == nullptr
	|| (raw() == ERR)
	|| (noecho()) == ERR
	|| (keypad(stdscr, 1)) == ERR)
		throw new GraphicalInitError("Error in Ncurses init\n");
}

/*
** TODO   Trouver un bypass pour throw on endwin error
**
**	if ((endwin()) == ERR)
**		throw new GraphicalCleanupError("Error on Ncurses exit\n");
 */

LNcurses::~LNcurses()
{
	endwin();
}

void	LNcurses::clear()
{
	if ((wclear(_window)) == ERR
	|| (wnoutrefresh(_window)) == ERR
	|| (wrefresh(_window)) == ERR)
		throw new GraphicalInLibError("Error in screen clear Ncurses\n");
}

void	LNcurses::drawDisp(Disp &disp)
{
	try {
		Position st = std::make_pair((size_t) std::get<0> (disp.position),
		(size_t) std::get<1> (disp.position));

		_moveCursor(st);
		printw("%c", disp.character);
	} catch (const GraphicalInLibError &e) {
		std::string str(e.what());
		throw new GraphicalInLibError(str + "\nError on drawing Disp character\n", e.getComponent());
	}
}

void	LNcurses::drawButton(Button &button)
{
	try {
		Position st = std::make_pair((size_t) std::get<0> (button.pos),
		(size_t) std::get<1> (button.pos));

		_moveCursor(st);	
		printw("%s", button.text.c_str());
	} catch (const GraphicalInLibError &e) {
		std::string str(e.what());
		throw new GraphicalInLibError(str + "\nError on drawing button\n", "Ncurses");
	}
}

void	drawScene(Scene &scene)
{
	try {

	} catch (const GraphicalInLibError &e) {
		std::string str(e.what());
		throw new GraphicalInLibError(str + "\nError on drawing scene\n", e.getComponent());
	}
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
	_moveCursor(text.pos);
	_print_text(text.text);
	_refreshScreen();
}

void    LNcurses::_moveCursor(Position pos)
{
	if ((move((int) std::get<0> (pos), (int) std::get<1> (pos))) == ERR)
		throw new GraphicalInLibError("Error in moving the pointer to print in Ncurses\n");
}

void    LNcurses::_refreshScreen()
{
	if ((refresh()) == ERR)
		throw new GraphicalInLibError("Error in refreshing Ncurses\n");
}

void    LNcurses::_print_text(std::string text)
{
	if ((printw("%s", text.c_str())) == ERR)
		throw new GraphicalInLibError("Error in printing in Ncurses\n");
}
