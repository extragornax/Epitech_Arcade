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
# include "Scene.hpp"
# include "Utils.hpp"

class   Nibbler : public IGame
{
public:
        // Ctor
        Nibbler();

        // Dtor
        ~Nibbler() override;

        // Member functions
	Scene	&updateScene(std::string event) override;
	void	saveScore(std::string nickname) override;
	void	menuPause() override;
	bool	endGame() override;
	gameStatus	getStatus() override;

	// Public properties

private:
	// Private member functions
        void	_setBoard();
	void	_spawnFood();
	void	_updateBoard(Board &board, std::string event);
	void	_moveSideway(Board &board, long unsigned int i, long unsigned int j,
			     long unsigned int i2, long unsigned int j2, int incr);
	void	_moveVertical(Board &board, long unsigned int i, long unsigned int j,
			      long unsigned int i2, long unsigned int j2, int incr);
	
private:
        // Properties
        Scene			_nibblerScene;
	std::list<Position>	_snake;
	size_t			_score;
        bool			_endgame;
	gameStatus		_gameStatus;
};

#endif /* NIBBLER_HPP_ */
