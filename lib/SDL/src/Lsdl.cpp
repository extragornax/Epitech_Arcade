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
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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
			throw std::string ("Cannot load SDL library\n" + str);
		}
		if ((_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL)) == NULL) {
			std::string str(SDL_GetError());
			throw std::string ("Cannot open SDL window\n" + str);
		}
		if ((_screen = SDL_GetWindowSurface(_window)) == NULL) {
			std::string str(SDL_GetError());
			throw std::string ("Cannot retrieve screen from SDL window\n" + str);
		}
		if ((_render = SDL_CreateRenderer(_window, -1, 0)) == NULL) {
			std::string str(SDL_GetError());
			throw std::string ("Cannot create SDL render screen\n" + str);
		}
	} catch (std::string const &str) {
		throw new GraphicalInitError(str, "SDL");
	}
}

Lsdl::~Lsdl()
{
	SDL_DestroyWindow(_window);
	SDL_FreeSurface(_screen);
	SDL_Quit();
}


void Lsdl::clear()
{
	SDL_RenderClear(_render);
}

void Lsdl::drawText(Text &text)
{
	SDL_Color color = {(Uint8)text.color.r, (Uint8)text.color.g, (Uint8)text.color.b, (Uint8)text.color.a};
	SDL_Surface *textToDraw = NULL;
	SDL_Rect position;
	TTF_Font *font = NULL;

	position.x = std::get<0> (text.pos);
	position.y = std::get<1> (text.pos);

	TTF_Init();
	font = TTF_OpenFont(text.font.c_str(), text.size);
	textToDraw = TTF_RenderText_Shaded(font, text.text.c_str(), color, SDL_Color{0, 0, 0, 0});
	SDL_BlitSurface(textToDraw, NULL, _screen, &position);
	SDL_FreeSurface(textToDraw);
	TTF_CloseFont(font);
	TTF_Quit();
}

void Lsdl::drawDisp(Disp &disp)
{
	SDL_Surface *toDraw = NULL;
	SDL_Rect position;

	toDraw = IMG_Load(disp.path.c_str());
	position.x = std::get<0> (disp.pos);
	position.y = std::get<1> (disp.pos);
	SDL_BlitSurface(toDraw, NULL, _screen, &position);
	SDL_FreeSurface(toDraw);
}

void Lsdl::drawButton(Button &button)
{
	SDL_Surface *toDraw = NULL;
	SDL_Rect position;

	toDraw = IMG_Load(button.sprite.c_str());
	position.x = std::get<0> (button.pos);
	position.y = std::get<1> (button.pos);
	SDL_BlitSurface(toDraw, NULL, _screen, &position);
	SDL_FreeSurface(toDraw);
}

void Lsdl::drawScene(Scene &scene)
{
	std::string title = scene.getTitle();
	SDL_Surface *toDraw = NULL;
	SDL_Texture *toDrawText = NULL;
	SDL_Rect position;
	double angle;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			toDraw = IMG_Load(scene.getBoardGame().getSprites(std::make_pair(i, j)).at(0).c_str());
			position.x = (SCREEN_WIDTH / 2 - ((WIDTH_BOARD * PIX_SIZE) / 2)) + j * PIX_SIZE;
			position.y = (SCREEN_HEIGHT / 2 - ((HEIGHT_BOARD * PIX_SIZE) / 2)) + i * PIX_SIZE;
			switch(scene.getBoardGame().getDirection(std::make_pair(i, j))) {
			case NORTH:
				angle = 0;
				break;
			case SOUTH:
				angle = 180;
				break;
			case WEST:
				angle = 90;
				break;
			default:
				angle = 270;
				break;
			}
					
			toDrawText = SDL_CreateTextureFromSurface(_render, toDraw);
			SDL_RenderCopyEx(_render, toDrawText, NULL, NULL, angle, NULL, SDL_FLIP_NONE);
			SDL_FreeSurface(toDraw);
			//Du coup, il manque une position a mettre dans le second NULL.. mais c'est plus chiant que ca.
			//SDL_BlitSurface(toDraw, NULL, _screen, &position);
		}
	}
}

void Lsdl::display()
{
	SDL_RenderPresent(_render);
}

void Lsdl::playSound(const std::string &path)
{
	
}

void Lsdl::stopSound(const std::string &path)
{

}

size_t Lsdl::getKey()
{
	SDL_Event	*_event = NULL;
	size_t		to_find = 0;

	SDL_PollEvent(_event);
	if (_event != NULL) {
		if (_event->type == SDL_KEYDOWN) {
			SDL_KeyboardEvent key = _event->key;
			switch (key.keysym.sym) {
				case SDLK_LEFT:
					to_find = 1;
					break;
				case SDLK_RIGHT:
					to_find = 2;
					break;
				case SDLK_UP:
					to_find = 3;
					break;
				case SDLK_DOWN:
					to_find = 4;
					break;
				case SDLK_p:
					to_find = 5;
					break;
				case SDLK_ESCAPE:
					to_find = 6;
					break;
				case SDLK_BACKSPACE:
					to_find = 7;
					break;
				case SDLK_r:
					to_find = 8;
					break;
				case SDLK_HOME:
					to_find = 9;
					break;
				case SDLK_END:
					to_find = 10;
					break;
				case SDLK_PAGEUP:
					to_find = 11;
					break;
				case SDLK_PAGEDOWN:
					to_find = 12;
					break;
			}
		}
	}
	return to_find;
}
