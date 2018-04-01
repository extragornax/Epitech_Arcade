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
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.hpp"
#include "Utils.hpp"
#include "Lsfml.hpp"
#include "Errors.hpp"

Lsfml::Lsfml()
	: _window(sf::VideoMode(800, 600), "Arcade"), _buffer(), _sound()
{
	_window.setFramerateLimit(60);
}

Lsfml::~Lsfml()
{
}

/*
** TODO   Dictionnaire Event(get Key)/drawScene/display?
**
 */
 

void	Lsfml::clear()
{
	_window.clear(sf::Color::Black);
}

void	Lsfml::playSound(const std::string &path)
{
	try
	{
		if (_buffer.loadFromFile(path) == false)
			throw std::string("loadFromFile: couldn't load sound\n");
		else {
			_sound.setBuffer(_buffer);
			_sound.play();
			_sound.setLoop(true);
		}
	} catch(std::string const &str) {
		throw new GraphicalInLibError(str, "SFML");
	}
}

void	Lsfml::stopSound(const std::string &path)
{
	(void) path;
	_sound.stop();
}


void	Lsfml::drawDisp(Disp &disp)
{
	try
	{
		sf::Texture texture;
		if (texture.loadFromFile(disp.path) == false)
			throw std::string("loadFromFile: couldn't load texture\n");
		else {
			sf::Sprite toDraw;
			toDraw.setTexture(texture);
			toDraw.setPosition(std::get<0> (disp.position), std::get<1> (disp.position));
			_window.draw(toDraw);
		}
	} catch(std::string const &str) {
		throw new GraphicalInLibError(str, "SFML");
	}
}


void	Lsfml::drawButton(Button &button)
{
	try
	{
		sf::Texture texture;
		if (texture.loadFromFile(button.sprite) == false)
			throw std::string("loadFromFile: couldn't load texture\n");
		else {
			sf::Sprite toDraw;
			toDraw.setTexture(texture);
			toDraw.setPosition(std::get<0> (button.pos), std::get<1> (button.pos));
			_window.draw(toDraw);
		}
	} catch(std::string const &str) {
		throw new GraphicalInLibError(str, "SFML");
	}
}

/*
char	Lsfml::getKey()
{
	char ret;

	if ((ret = getch()) == ERR)
		throw new GraphicalInLibError("Error in retrieving user input key\n");
	return ret;
}
*/

void    Lsfml::drawText(Text &text)
{
	try
	{
		sf::Font font;
		if (font.loadFromFile(text.font) == false)
			throw std::string("loadFromFile: couldn't load font\n");
		else {
			sf::Text toDraw(text.text, font, text.size);
			toDraw.setColor(sf::Color(text.color.r, text.color.g, text.color.b, text.color.a));
			toDraw.setPosition(std::get<0> (text.pos), std::get<1> (text.pos));
			_window.draw(toDraw);
		}
	} catch(std::string const &str) {
		throw new GraphicalInLibError(str, "SFML");
	}
}
