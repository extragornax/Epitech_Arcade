//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// sfml header
//

#pragma once

#include <SDL/SDL.h>
#include <string>
#include "ILib.hpp"

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
	//sf::RenderWindow _window;
	//sf::SoundBuffer _buffer;
	//sf::Sound	_sound;
};
