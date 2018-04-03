//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// main.cpp
//

#include <unistd.h>
#include "Errors.hpp"
#include "lib_open.hpp"
#include "IGame.hpp"
#include "ILib.hpp"

int	main(int ac, char **av)
{
	Dlloader *load_graph;
	Dlloader *load_game;

	if (ac != 2) {
		std::cout << "The graphical lib is missing\n";
		return 84;
	}
	try {
		load_graph = new Dlloader(av[1]);
		load_game = new Dlloader("./games/lib_arcade_nibbler.so");
	} catch (const DLError *e) {
		std::string str = e->what();
		std::cout << "CRASH: [" << str << "]\n";
		throw e;
	}
	ILib *lib_handler;
	IGame *game_handler;
	try {
		lib_handler = load_graph->createLibSym();
		game_handler = load_game->createGameSym();
	} catch (const GraphicalInitError *e) {
		std::string str = e->what();
		std::cout << "CRASH INIT: [" << str << "]\n";
	}

	try {
		std::clock_t startTime = std::clock();
	        size_t event = 0;
		while (game_handler->endGame() == false) {
			size_t tryEvent = lib_handler->getKey();
			event = (tryEvent == 0) ? event : tryEvent;
			std::clock_t elapsedTime = std::clock();
			std::clock_t deltaTime = elapsedTime - startTime;

			if (deltaTime > 250000) {
				lib_handler->drawScene(game_handler->updateScene(event));
				lib_handler->display();
				startTime = std::clock();
				event = 0;
			}
//			usleep(500000);
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
