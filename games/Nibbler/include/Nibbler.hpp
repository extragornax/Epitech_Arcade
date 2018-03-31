//
// EPITECH PROJECT, 2018
// include
// File description:
// Nibbler class header
//

#ifndef NIBBLER_HPP_
# define NIBBLER_HPP_

# include "IGame.hpp"
# include "Board.hpp"

class   Nibbler : public IGame
{
public:
        // Ctor
        Nibbler();

        // Dtor
        ~Nibbler() override;

        // Member functions
	Scene	&updateScene(int event) override;
	void	saveScore() override;
	void	menuPause() override;
	bool	endGame() override;
	gameState	getStatus() override;

	// Public properties

private:
	// Private member functions
        void	&_setBoard();
	void	_spawnFood();
	void	_updateBoard();
	void	_moveSideway(Board &board, int i, int j, int i2, int j2, int incr);
	void	_moveUp();
	void	_moveDown();
	
private:
        // Properties
        Scene			_nibblerScene;
	std::list<Position>	_snake;
	size_t			_score;
	std::bool		_endgame;
	gameState		_gameStatus;
};

#endif /* NIBBLER_HPP_ */
