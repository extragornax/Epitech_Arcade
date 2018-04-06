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
			if (strcmp(lib->d_name, ".") != 0 && strcmp(lib->d_name, "..") != 0 && strcmp(lib->d_name, "Makefile") != 0) {
				save.append(lib->d_name);
				libs.push_back(save);
				save = path;
			}
		}
		closedir(resourcesDir);
	}
	return libs;
}

void	loadMenu(/*std::unique_ptr<ILib *> lib_handler*/ILib *lib_handler, std::string &lib_path, std::string &game_path)
{
	std::vector<Button> games;
	std::vector<Button> libs;
	std::vector<Button> *ptr = &games;
	size_t event = 0;
	std::vector<std::string> graph_libs = getResources("./lib/");
	std::vector<std::string> games_libs = getResources("./games/");

	size_t x = 50;
	size_t y = 20;
	for (std::vector<std::string>::iterator it = graph_libs.begin(); it != graph_libs.end(); ++it) {
		if (it == graph_libs.begin())
			libs.push_back(Button{*it, "./games/Nibbler/misc/sprites/background.png", Position(y, x), true});
		else
			libs.push_back(Button{*it, "./games/Pacman/misc/sprites/walls.png", Position(y, x), false});
 		y += 5;
	}
	y = 20;
	x = 10;
	for (std::vector<std::string>::iterator it = games_libs.begin(); it != games_libs.end(); ++it) {
		if (it == games_libs.begin())
			games.push_back(Button{*it, "./games/Nibbler/misc/sprites/snake_head.png", Position(y, x), true});
		else
			games.push_back(Button{*it, "./games/Pacman/misc/sprites/pacman.png", Position(y, x), false});
		y += 5;
	}
	for (std::vector<std::string>::iterator it = games_libs.begin(); it != games_libs.end(); ++it) {
		std::cout << *it << std::endl;
	}
	//while (1);

	/*games.push_back(Button{"pacman", "./games/Nibbler/misc/sprites/snake_head.png", Position(20, 10), true});
	games.push_back(Button{"nibbler", "./games/Pacman/misc/sprites/pacman.png", Position(25, 10), false});

	libs.push_back(Button{"ncurses", "./games/Nibbler/misc/sprites/background.png", Position(20, 50), true});
	libs.push_back(Button{"sfml", "./games/Nibbler/misc/sprites/walls.png", Position(25, 50), false});
	libs.push_back(Button{"sdl", "./games/Nibbler/misc/sprites/food.png", Position(30, 50), false});*/

	while ((event = lib_handler->getKey()) != 13) {
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
			//game_path = "./games/lib_arcade_";
			game_path += (*it).text;
			//game_path += ".so";
		}
	}
	for (std::vector<Button>::iterator it = libs.begin(); it != libs.end(); ++it) {
		if ((*it).active == true) {
			//lib_path = "./lib/lib_arcade_";
			lib_path += (*it).text;
			//lib_path += ".so";
		}
	}
	lib_handler->clear();
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
//	std::unique_ptr<ILib *> lib_handler;
	ILib *lib_handler;
	IGame *game_handler;
	try {
//		lib_handler = std::make_unique<ILib *> (load_graph->createSym());
		lib_handler = load_graph->createSym();
		//game_handler = load_game->createSym();
	} catch (const GraphicalInitError *e) {
		std::string str = e->what();
		std::cout << "CRASH INIT: [" << str << "]\n";
	}

	std::string lib_path;
	std::string games_path;
	
	loadMenu(lib_handler, lib_path, games_path);
	delete (lib_handler);
//	std::unique_ptr<ILib *> lib_handler;
	try {
		load_graph = new Dlloader<ILib> (lib_path);
		load_game = new Dlloader<IGame> (games_path);
	} catch (const DLError *e) {
		std::string str = e->what();
		std::cout << "CRASH: [" << str << "]\n";
		throw e;
	}
	try {
		lib_handler = /*std::make_unique<ILib *>*/ load_graph->createSym();
		game_handler = /*std::make_unique<IGame *>*/ load_game->createSym();
	} catch (const GraphicalInitError *e) {
		std::string str = e->what();
		std::cout << "CRASH INIT: [" << str << "]\n";
	}
	
	try {
		size_t event = 0;
		int libPos = 0;
		int gamePos = 0;
		while (graph_libs[libPos] != lib_path)
			++libPos;
		while (games_libs[gamePos] != games_path)
			++gamePos;
		while (game_handler->endGame() == false) {
			event = lib_handler->getKey();
			if (event == 5)
				game_handler->menuPause();
			if (event == 6)
				break;
			if (event >= 8 && event <= 12) {
				switch (event) {
				case 8:
					delete (game_handler);
					delete (load_game);
					load_game = new Dlloader<IGame> (games_libs[gamePos]);
					game_handler = load_game->createSym();
					break;
				case 9:
					delete (lib_handler);
					delete (load_graph);
					--libPos;
					libPos = (libPos == -1) ? graph_libs.size() - 1 : libPos;
					load_graph = new Dlloader<ILib> (graph_libs[libPos]);
					lib_handler = load_graph->createSym();
					break;
				case 10:
					delete (lib_handler);
					delete (load_graph);
					++libPos;
					libPos = (libPos == (int) graph_libs.size()) ? 0 : libPos;
					load_graph = new Dlloader<ILib> (graph_libs[libPos]);
					lib_handler = load_graph->createSym();
					break;
				case 11:
					delete (game_handler);
					delete (load_game);
					std::cout << "am i here ? "<< std::endl;
					--gamePos;
					gamePos = (gamePos == -1) ? games_libs.size() - 1 : gamePos;
					load_game = new Dlloader<IGame> (games_libs[gamePos]);
					game_handler = load_game->createSym();
					break;
				case 12:
					delete (game_handler);
					delete (load_game);
					++gamePos;
					gamePos = (gamePos == (int) games_libs.size()) ? 0 : gamePos;
					load_game = new Dlloader<IGame> (games_libs[gamePos]);
					game_handler = load_game->createSym();
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
