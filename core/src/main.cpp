//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// main.cpp
//

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include "Errors.hpp"
#include "lib_open.hpp"
#include "IGame.hpp"
#include "ILib.hpp"

std::vector<std::string> getResources(std::string path)
{
	DIR *resourcesDir;
	struct dirent *lib;
	std::vector<std::string> libs;
	std::string save = path;
	unsigned char isFile = 0x8;

	if ((resourcesDir = opendir(path.data()))) {
		while ((lib = readdir(resourcesDir))) {
			if (lib->d_type != isFile)
				continue;
			if (strcmp(lib->d_name, ".") != 0 && strcmp(lib->d_name, "..") != 0) {
				save.append(lib->d_name);
				libs.push_back(save);
				save = path;
			}
		}
		closedir(resourcesDir);
	}
	return libs;
}

void	loadMenu(ILib *lib_handler, std::string &lib_path, std::string &game_path)
{
	std::vector<Button> games;
	std::vector<Button> libs;
	std::vector<Button> *ptr = &games;
	size_t event = 0;

	games.push_back(Button{"nibbler", "./games/Nibbler/misc/sprites/snake_head.png", Position(10, 10), true});
	games.push_back(Button{"pacman", "./games/Pacman/misc/sprites/pacman.png", Position(10, 40), false});

	libs.push_back(Button{"ncurses", "./games/Nibbler/misc/sprites/background.png", Position(100, 10), true});
	libs.push_back(Button{"sfml", "./games/Nibbler/misc/sprites/walls.png", Position(100, 40), false});
	libs.push_back(Button{"sdl", "./games/Nibbler/misc/sprites/food.png", Position(100, 70), false});

	while ((event = lib_handler->getKey()) != 7) {
		for (std::vector<Button>::iterator it = games.begin(); it != games.end(); ++it) {
			lib_handler->drawButton(*it);
		}
		for (std::vector<Button>::iterator it = libs.begin(); it != libs.end(); ++it) {
			lib_handler->drawButton(*it);
		}
		if (event == 1)
			ptr = &games;
		else if (event == 2)
			ptr = &libs;
		if (event == 4)
		{
			for (std::vector<Button>::iterator it = (*ptr).begin();
			     it != (*ptr).end(); ++it)
				if ((*it).active == true) {
					(*it).active = false;
					if ((it + 1) == (*ptr).end())
						(*ptr).front().active = true;
					else {
						++it;
							(*it).active = true;
					}
					break ;
				}
		}
		else if (event == 3)
		{
			for (std::vector<Button>::iterator it = (*ptr).begin();
			     it != (*ptr).end(); ++it)
				if ((*it).active == true) {
					(*it).active = false;
					if ((it) == (*ptr).begin())
						(*ptr).back().active = true;
					else {
						--it;
						(*it).active = true;
					}
					break ;
				}
		}
		usleep(100000);
		lib_handler->display();
	}
	for (std::vector<Button>::iterator it = games.begin(); it != games.end(); ++it) {
		if ((*it).active == true) {
			game_path = "./games/lib_arcade_";
			game_path += (*it).text;
			game_path += ".so";
		}
	}
	for (std::vector<Button>::iterator it = libs.begin(); it != libs.end(); ++it) {
		if ((*it).active == true) {
			lib_path = "./lib/lib_arcade_";
			lib_path += (*it).text;
			lib_path += ".so";
		}
	}
}

int	main(int ac, char **av)
{
	Dlloader<ILib> *load_graph;
	Dlloader<IGame> *load_game;
	std::vector<std::string> graph_libs = getResources("./lib/");
	std::vector<std::string> games_libs = getResources("./games/");

	if (ac != 2) {
		std::cout << "The graphical lib is missing\n";
		return 84;
	}
	try {
		load_graph = new Dlloader<ILib> (av[1]);
		//load_game = new Dlloader<IGame> ("./games/lib_arcade_nibbler.so");
	} catch (const DLError *e) {
		std::string str = e->what();
		std::cout << "CRASH: [" << str << "]\n";
		throw e;
	}
	ILib *lib_handler;
	IGame *game_handler;
	try {
		lib_handler = load_graph->createSym();
		//game_handler = load_game->createSym();
	} catch (const GraphicalInitError *e) {
		std::string str = e->what();
		std::cout << "CRASH INIT: [" << str << "]\n";
	}

	std::string lib_path;
	std::string games_path;
	
	loadMenu(lib_handler, lib_path, games_path);
	delete lib_handler;
	try {
		load_graph = new Dlloader<ILib> (lib_path);
		load_game = new Dlloader<IGame> (games_path);
	} catch (const DLError *e) {
		std::string str = e->what();
		std::cout << "CRASH: [" << str << "]\n";
		throw e;
	}
	try {
		lib_handler = load_graph->createSym();
		game_handler = load_game->createSym();
	} catch (const GraphicalInitError *e) {
		std::string str = e->what();
		std::cout << "CRASH INIT: [" << str << "]\n";
	}
	
	try {
		size_t event = 0;
		int libPos = 0;
		while (graph_libs[libPos] != lib_path)
			++libPos;
		while (game_handler->endGame() == false) {
			event = lib_handler->getKey();
			if (event == 6)
				break;
			if (event >= 9 && event <= 10) {// 11 & 12 to be added
				switch (event) {
				case 9:
					delete (load_graph);
//					delete lib_handler;
					--libPos;
					libPos = (libPos == -1) ? graph_libs.size() - 1 : libPos;
					load_graph = new Dlloader<ILib> (graph_libs[libPos]);
					lib_handler = load_graph->createSym();
					break;
				case 10:
					delete (load_graph);
//					delete (lib_handler);
					++libPos;
					libPos = (libPos == (int) graph_libs.size()) ? 0 : libPos;
					load_graph = new Dlloader<ILib> (graph_libs[libPos]);
					lib_handler = load_graph->createSym();
					break;
				}
			}
			lib_handler->drawScene(game_handler->updateScene(event));
			lib_handler->display();
		}
	} catch (const std::exception *e) {
		std::string str = e->what();
		std::cout << "CRASH: [" << str << "]\n";
		delete lib_handler;
		delete game_handler;
		//throw e;
	}
	return 0;
}
