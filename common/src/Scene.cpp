//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Scene.cpp
//

#include "Scene.hpp"

Scene::Scene() : _boardGame()
{

}

Scene::~Scene()
{

}

Board	&Scene::getBoardGame()
{
	return _boardGame;
}

Board	&Scene::getBoardFooter()
{
	return _boardFooter;
}

std::string	&Scene::getTitle()
{
	return _title;
}

std::clock_t	&Scene::getClock()
{
	return _clock;
}

size_t	Scene::getScore()
{
	return _score;
}
