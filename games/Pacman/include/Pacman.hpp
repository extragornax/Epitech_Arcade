//
// EPITECH PROJECT, 2018
// include
// File description:
// Pacman class header
//

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

# include <string>
# include "IGame.hpp"
# include "Board.hpp"
# include "Scene.hpp"
# include "Utils.hpp"

struct	Ghost
{
	Position		pos;
	std::vector<char>	chars;
	std::vector<std::string>	sprites;
};

class   Pacman : public IGame
{
public:
        // Ctor
        Pacman();

        // Dtor
        ~Pacman() override;

        // Member functions
	Scene	&updateScene(size_t event) override;
	void	saveScore(std::string nickname) override;
	void	menuPause() override;
	bool	endGame() override;
	gameStatus	getStatus() override;

	// Public properties

private:
	// Private member functions
        void	_setBoard();
	void	_setHeader();
	void	_updateBoard(Board &board, size_t event);
	void	_updateGhosts(Board &board, int idx);
	void	_moveSideway(Board &board, int i, int j, int incr);
	void	_moveVertical(Board &board, int i, int j, int incr);
	
private:
        // Properties
	std::clock_t		_startClock;
        Scene			_pacmanScene;
	Position		_pacman;
	std::vector<Ghost>	_ghosts;
	int			_foodCounter;
	size_t			_score;
        bool			_endgame;
	gameStatus		_gameStatus;
	int			_timeLimit;
};

static const char	baseMap[HEIGHT_BOARD][WIDTH_BOARD] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
	{'1', ' ', '1', '1', '1', ' ', '1', '1', '1', ' ', '1', ' ', '1', '1', ' ', '1', '1', '1', ' ', '1'},
	{'1', ' ', '1', ' ', ' ', ' ', '1', '1', '1', ' ', '1', '1', '1', '1', ' ', ' ', ' ', '1', ' ', '1'},
	{'1', ' ', '1', ' ', '1', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', '1', '1', ' ', '1'},
	{'1', ' ', ' ', ' ', '1', ' ', '1', '1', ' ', '1', ' ', '1', '1', '1', ' ', ' ', ' ', '1', ' ', '1'},
	{'1', ' ', '1', '1', '1', ' ', '1', ' ', ' ', '1', ' ', '1', '1', '1', ' ', '1', '1', '1', ' ', '1'},
	{'1', ' ', ' ', ' ', ' ', ' ', '1', ' ', '1', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
	{'1', ' ', '1', '1', '1', ' ', '1', ' ', '1', '1', ' ', '1', '1', ' ', '1', '1', '1', '1', ' ', '1'},
	{'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', '1'},
	{'1', ' ', '1', '1', ' ', '1', ' ', '1', '1', '1', '1', '1', '1', ' ', '1', '1', ' ', '1', ' ', '1'},
	{'1', ' ', ' ', '1', ' ', '1', ' ', '1', '2', '2', '2', '2', '1', ' ', '1', '1', ' ', '1', ' ', '1'},
	{'1', '1', ' ', '1', ' ', '1', ' ', '1', '1', '1', '1', '1', '1', ' ', '1', '1', ' ', '1', ' ', '1'},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '3', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' '},
	{'1', ' ', '1', '1', '1', ' ', '1', ' ', '1', '1', '1', '1', ' ', '1', ' ', ' ', ' ', '1', ' ', '1'},
	{'1', ' ', '1', '1', '1', ' ', '1', ' ', ' ', '1', '1', '1', ' ', '1', ' ', '1', ' ', '1', ' ', '1'},
	{'1', ' ', '1', ' ', ' ', ' ', '1', '1', ' ', ' ', '1', '1', ' ', '1', ' ', ' ', ' ', ' ', ' ', '1'},
	{'1', ' ', '1', ' ', '1', ' ', '1', '1', '1', ' ', '1', '1', ' ', '1', '1', '1', '1', '1', ' ', '1'},
	{'1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	
};

#endif /* PACMAN_HPP_ */
