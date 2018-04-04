//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// SDL header
//

#pragma once

#include <SDL/SDL.h>
#include <string>
#include "ILib.hpp"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Lsdl : public ILib {
	public:
		Lsdl();
		~Lsdl();
		void clear();
		void drawText(Text &text);
		void drawDisp(Disp &disp);
		void drawButton(Button &button);
		void drawScene(Scene &scene);
		void display();
		void playSound(const std::string &path);
		void stopSound(const std::string &path);
		size_t getKey();

	private:
		SDL_Window	*_window;
};
