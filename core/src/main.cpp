//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// main.cpp
//

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
		std::unique_ptr<ILib> lib_handler = load_graph->createLibSym();
		std::unique_ptr<IGame> game_handler = load_game->createGameSym();

		(void) ac;
		(void) av;
		while (game_handler->endGame() == false) {
			lib_handler->drawScene(game_handler->updateScene(lib_handler->getKey()));
			lib_handler->display();
		}
	return 0;
}
