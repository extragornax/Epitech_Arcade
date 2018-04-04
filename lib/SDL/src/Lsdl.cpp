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
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1)
			throw std::string ("Cannot load SDL library\n");
	} catch (std::string const &str) {
		throw new GraphicalInLibError(str, "SDL");
	}
}

Lsdl::~Lsdl()
{
}
