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

extern "C"
{
	ILib *createLib()
	{
		return new Lsfml();
	}
}

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

std::string	Lsfml::getKey()
{
	size_t to_find = 0;
/*
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code) {
		case sf::Keyboard::Left:
			to_find = 1;
			break;
		case sf::Keyboard::Right:
			to_find = 2;
			break;
		case sf::Keyboard::Up:
			to_find = 3;
			break;
		case sf::Keyboard::Down:
			to_find = 4;
			break;
		case sf::Keyboard::P:
			to_find = 5;
			break;
		case sf::Keyboard::Escape:
			to_find = 6;
			break;
		case sf::Keyboard::BackSpace:
			to_find = 7;
			break;
		case sf::Keyboard::R:
			to_find = 8;
			break;
		case sf::Keyboard::Home:
			to_find = 9;
			break;
		case sf::Keyboard::End:
			to_find = 10;
			break;
		case sf::Keyboard::PageDown:
			to_find = 11;
			break;
		case sf::Keyboard::PageUp:
			to_find = 12;
			break;
		default:
			to_find = 0;
			break;
		}
		}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			to_find = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			to_find = 2;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			to_find = 3;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			to_find = 4;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			to_find = 5;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			to_find = 6;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			to_find = 7;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			to_find = 8;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
			to_find = 9;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::End))
			to_find = 10;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
			to_find = 11;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
			to_find = 12;
	for (unsigned int i = 0; i < DICO.size(); i++) {
		if (std::get<0> (DICO[i]) == to_find) {
				return std::get<1> (DICO[i]);
			}
	}
	return "NO_EVENT";
}


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

void	Lsfml::drawScene(Scene &scene)
{
	std::string title = scene.getTitle();
	sf::Vector2u size = _window.getSize();



/*		try
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
		}*/

		sf::Texture texture;
		sf::Sprite toDraw;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; i < 20; j++) {
			try  {
				if (texture.loadFromFile(scene.getBoardGame().getSprites(std::make_pair(i, j)).at(0)) == false)
				throw std::string("loadFromFile: couldn't load texture\n");
			else {
				toDraw.setTexture(texture);
				toDraw.setPosition((float) j * size.x, (float)i * size.y);
				switch(scene.getBoardGame().getDirection(std::make_pair(i, j))) {
				case NORTH:
					toDraw.setRotation(-90);
					break;
				case SOUTH:
					toDraw.setRotation(90);
					break;
				case WEST:
					toDraw.setRotation(180);
					break;
				default:
					toDraw.setRotation(0);
					break;
				}
			}
			} catch (std::string const &str) {
				throw new GraphicalInLibError(str, "SFML");
			}
			
		}
	}	
}

void Lsfml::display()
{
	return ;
}
