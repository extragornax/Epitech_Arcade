//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// main.cpp
//

#include "lib_open.hpp"
#include "IGame.hpp"
#include "ILib.hpp"

int	main(int ac, char **av)
{
	auto load_graph = new Dlloader("./lib/lib_arcade_ncurses.so");
	auto load_game = new Dlloader("./game/lib_arcade_nibbler.so");
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
