//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ncurses constructor
//

#include <chrono>
#include <ctime>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <string.h>
#include <curses.h>
#include "Board.hpp"
#include "Utils.hpp"
#include "LNcurses.hpp"
#include "Errors.hpp"

extern "C"
{
	ILib *create()
	{
		return new LNcurses;
	}
}

LNcurses::LNcurses()
	: _window(nullptr),
	_start_game(std::make_pair(0, 0))
{
	if ((_window = initscr()) == nullptr)
		throw new GraphicalInitError("Error in screen init\n", "Ncurses");
	if (nodelay(_window, TRUE) == ERR)
		throw new GraphicalInitError("Error in no delay\n", "Ncurses");
	if (noecho() == ERR)
		throw new GraphicalInitError("Error in noecho init\n", "Ncurses");
	if (keypad(stdscr, 1) == ERR)
		throw new GraphicalInitError("Error in keypad init\n", "Ncurses");
	if (nodelay(stdscr, TRUE) == ERR)
		throw new GraphicalInitError("Error in nodelay init\n", "Ncurses");
	if (curs_set(0) == ERR)
		throw new GraphicalInitError("Error in curs_set init\n", "Ncurses");
	start_color();
	_get_winSize();
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
		throw new GraphicalInLibError("Error in screen clear\n", "Ncurses");
}


void	LNcurses::playSound(const std::string &path)
{
	(void) path;
}

void	LNcurses::stopSound(const std::string &path)
{
	(void) path;
}

void	LNcurses::drawDisp(Disp &disp)
{
	try {
		Position st = std::make_pair((size_t) std::get<0> (disp.pos),
		(size_t) std::get<1> (disp.pos));

		_moveCursor(st);
		printw("%c", disp.character);
	} catch (const GraphicalInLibError &e) {
		std::string str(e.what());
		throw new GraphicalInLibError(str + "\nError on drawing Disp character\n", "Ncurses");
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

void	LNcurses::drawScene(Scene &scene)
{
	try {
		_get_winSize();
		if (_screen_size.first < 21 ||_screen_size.second < 50) {
			mvprintw(1, 1, "%c", "Screen size must be 50 x 21 min");
			return;
		}

		std::string _title = scene.getTitle();
		int x = (std::get<0> (_screen_size) / 2) - (_title.length() / 2);
		int y = 1;
		mvprintw(x, y, "%s", _title.c_str());

		x = (std::get<0> (_screen_size) / 2) - (10);
		y = 4;
		std::clock_t now = std::clock();
		mvprintw(x, y, "Time: %im%i",  (int) std::chrono::duration<double, std::milli>(now - scene.getClock()).count() / 1000 / 60,
		(int) std::chrono::duration<double, std::milli>(now - scene.getClock()).count() / 1000);

		x = (std::get<0> (_screen_size) / 2) - (10);
		y = 6;
		mvprintw(x, y, "Score: %zu", scene.getScore());

		x = std::get<1> (_screen_size) / 2 - 10;
		y = 20;
		_start_game = std::make_pair(x, y);
		_moveCursor(_start_game);
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
//				init_color(COLOR_RED, scene.getBoardGame().getColorBackground(std::make_pair(i, j)).r, scene.getBoardGame().getColorBackground(std::make_pair(i, j)).g, scene.getBoardGame().getColorBackground(std::make_pair(i, j)).b);
//				init_color(COLOR_BLACK, scene.getBoardGame().getColorForeground(std::make_pair(i, j)).r, scene.getBoardGame().getColorForeground(std::make_pair(i, j)).g, scene.getBoardGame().getColorForeground(std::make_pair(i, j)).b);
				init_pair(1, COLOR_GREEN, COLOR_BLACK);
				attron(COLOR_PAIR(1) | A_BOLD);
				mvprintw(i + x, j + y, "%c", scene.getBoardGame().getCharacters(std::make_pair(i, j)).at(0));
				attroff(COLOR_PAIR(1));
			}
		}
	} catch (const GraphicalInLibError &e) {
		std::string str(e.what());
		throw new GraphicalInLibError(str + "\nError on drawing scene\n", "Ncurses");
	}
}

void	LNcurses::display()
{
	refresh();
}

size_t LNcurses::getKey()
{
	int ret = 0;
	size_t to_find = 0;

	if ((ret = getch()) == ERR)
		return 0;
	switch (ret) {
	case KEY_LEFT:
		to_find = 1;
		break;
	case KEY_RIGHT:
		to_find = 2;
		break;
	case KEY_UP:
		to_find = 3;
		break;
	case KEY_DOWN:
		to_find = 4;
		break;
	case 'P':
		to_find = 5;
		break;
	case ESCAPE_KEY:
		to_find = 6;
		break;
	case KEY_BACKSPACE:
		to_find = 7;
		break;
	case 'R':
		to_find = 8;
		break;
	case KEY_HOME:
		to_find = 9;
		break;
	case KEY_END:
		to_find = 10;
		break;
	case KEY_NPAGE:
		to_find = 11;
		break;
	case KEY_PPAGE:
		to_find = 12;
		break;
	case 10:
		to_find = 13;
		break;
	}
	return to_find;
/*	for (unsigned int i = 0; i < DICO.size(); i++) {
	if (std::get<0> (DICO[i]) == to_find) {
	return std::get<1> (DICO[i]);
	}
	}
	return "NO_EVENT";*/
	/*
	  auto it = std::find_if(DICO.begin(), DICO.end(),
	  [](const std::pair<size_t, std::string> &element){
	  return element.first == to_find;
	  }
	  );
	  return it;*/
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
		throw new GraphicalInLibError("Error in moving the pointer to print\n", "Ncurses");
}

void    LNcurses::_refreshScreen()
{
	if ((refresh()) == ERR)
		throw new GraphicalInLibError("Error in refreshing screen\n", "Ncurses");
}

void    LNcurses::_print_text(std::string text)
{
	if ((printw("%s", text.c_str())) == ERR)
		throw new GraphicalInLibError("Error in printing\n", "Ncurses");
}

void	LNcurses::_get_winSize()
{
	int x;
	int y;

	getmaxyx(_window, y, x);
	if (x == ERR || y == ERR)
		throw new GraphicalInLibError("Error in getting screen size", "Ncurses");
	_screen_size = std::make_pair(x, y);
}
