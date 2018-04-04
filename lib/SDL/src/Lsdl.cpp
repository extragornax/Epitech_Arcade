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
#include <SDL/SDL.h>
#include "Board.hpp"
#include "Utils.hpp"
#include "Lsdl.hpp"
#include "Errors.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

extern "C"
{
	ILib *createLib()
	{
		return new Lsdl();
	}
}

Lsdl::Lsdl()
{
	try {
		SDL_ClearError();
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
			std::string str(SDL_GetError());
			throw std::string ("Cannot load SDL library\n" + str));
		}
		if ((_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL)) == NULL) {
			std::string str(SDL_GetError());
			throw std::string ("Cannot open SDL window\n" + str));
		}
	} catch (std::string const &str) {
		throw new GraphicalInitError(str, "SDL");
	}
}

Lsdl::~Lsdl()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}


void Lsdl::clear()
{

}

void Lsdl::drawText(Text &text)
{

}

void Lsdl::drawDisp(Disp &disp)
{

}

void Lsdl::drawButton(Button &button)
{

}

void Lsdl::drawScene(Scene &scene)
{

}

void Lsdl::display()
{

}

void Lsdl::playSound(const std::string &path)
{

}

void Lsdl::stopSound(const std::string &path)
{

}

size_t Lsdl::getKey()
{

}