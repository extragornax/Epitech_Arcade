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
	
private:
        // Properties
        Scene	_nibblerScene;
	size_t	_score;
	std::string _nickname;
};

#endif /* NIBBLER_HPP_ */
