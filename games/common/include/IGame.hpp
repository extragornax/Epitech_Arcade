//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IGame class header
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

#include "Board.hpp"

class   IGame
{
public:
        // Dtor
        virtual ~IGame() = 0;
	
        // Member functions
	virtual Scene	&updateScene(Event last) = 0;
	virtual void	saveScore() = 0;
	virtual void	menuPause() = 0;
	virtual bool	endGame() = 0;
	virtual gameState	getStatus();
};

#endif /* IGAME_HPP_ */
