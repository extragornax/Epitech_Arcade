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
		load_game = new Dlloader<IGame> ("./games/lib_arcade_nibbler.so");
	} catch (const DLError *e) {
		std::string str = e->what();
		std::cout << "CRASH: [" << str << "]\n";
		throw e;
	}
	ILib *lib_handler;
	IGame *game_handler;
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
		while (graph_libs[libPos] != av[1])
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
