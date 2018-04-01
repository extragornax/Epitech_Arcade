//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// sfml header
//

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "ILib.hpp"

class Lsfml : public ILib {
        public:
		Lsfml();
		~Lsfml();
		void clear();
		void drawText(Text &text);
		void drawDisp(Disp &disp);
		void drawButton(Button &button);
		void drawScene(Scene &scene);
		void display();
		void playSound(const std::string &path);
		void stopSound(const std::string &path);
		char getKey();

        private:
		sf::RenderWindow _window;
		sf::SoundBuffer _buffer;
		sf::Sound	_sound;
};
