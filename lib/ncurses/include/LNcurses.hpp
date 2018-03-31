//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ncurses header
//

#pragma once

#include <curses.h>
#include "ILib.hpp"

class LNcurses : public ILib {
        public:
            LNcurses();
            ~LNcurses();
            void clear();
            void drawText(Text &text);
            void drawDisp(Disp &disp);
            void drawButton(Button &button);
            void drawScene(Scene &scene);
            void display();
            char getKey();

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