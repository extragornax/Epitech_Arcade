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
		std::cout << "Load libs done" << std::endl;
	} catch (const DLError *e) {
		std::string str = e->what();
		std::cout << "CRASH: [" << str << "]\n";
		throw e;
	}
	ILib *lib_handler;
	IGame *game_handler;
	try {
		game_handler = load_game->createGameSym();
		std::cout << "Init passed game" << std::endl;

		lib_handler = load_graph->createLibSym();
		std::cout << "Init passed lib" << std::endl;
	} catch (const GraphicalInitError *e) {
		std::string str = e->what();
		std::cout << "CRASH INIT: [" << str << "]\n";
		std::cout << "Init FAILED of libs" << std::endl;
	}
	std::cout << "Init passed of libs" << std::endl;
	try {

		while (game_handler->endGame() == false) {
			std::string ee = lib_handler->getKey();
			std::cout << "got key " << ee << std::endl;

			auto &scene = game_handler->updateScene(ee);
			std::cout << "sent key" << std::endl;

			std::cout << "Going to send Scene" << std::endl;

			lib_handler->drawScene(scene);
			std::cout << "drew scene" << std::endl;

			lib_handler->display();
			usleep(500000);
		}
	} catch (const std::out_of_range &e) {
		std::cout << "OUT OF RANGE " << e.what() << std::endl;
	} catch (const std::exception *e) {
		std::string str = e->what();
		std::cout << "CRASH: [" << str << "]\n";
		delete lib_handler;
		delete game_handler;
		//throw e;
	}
	return 0;
}
