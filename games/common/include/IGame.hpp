//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IGame class header
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

#include "Board.hpp"
#include "Scene.hpp"

class   IGame
{
public:
        // Dtor
        virtual ~IGame() = 0;

        // Member functions
	virtual Scene	&updateScene(std::string last) = 0;
	virtual void	saveScore(std::string nickname) = 0;
	virtual void	menuPause() = 0;
	virtual bool	endGame() = 0;
	virtual gameStatus	getStatus();
};

std::unique_ptr<IGame> createGame();

#endif /* IGAME_HPP_ */
