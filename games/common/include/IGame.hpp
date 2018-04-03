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
	virtual ~IGame() {};

	// Member functions
	virtual Scene	&updateScene(size_t last) = 0;
	virtual void	saveScore(std::string nickname) = 0;
	virtual void	menuPause() = 0;
	virtual bool	endGame() = 0;
	virtual gameStatus	getStatus() = 0;
};

#endif /* IGAME_HPP_ */
