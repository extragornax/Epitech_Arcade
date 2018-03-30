//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ncurses header
//

#ifndef LNCURSES_HPP_
# define LNCURSES_HPP_

#include <curses.h>
#include "ILib.hpp"

class LNcurses : public ILib {
        public:
            LNcurses();
            ~LNcurses();
            void clear();
            void drawText(Text &text);
            char getKey();

        public:
			void moveCursor(Position pos);
			void refreshScreen();
            void print_text(std::string text);
        
        private:
            char _getch;
            WINDOW *_window;
};

#endif /* LNCURSES_HPP_ */