//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ILib class header
//

#ifndef ILIB_HPP_
# define ILIB_HPP_

# include "Scene.hpp"

class   ILib
{
public:
	// Dtor
	virtual ~ILib() = 0;

	// Member functions
	virtual void	clear() = 0;
	virtual void	playSound(const std::string &path) = 0;
	virtual void	stopSoud(const std::string &path) = 0;
	virtual void	drawText(Text &text) = 0;
	virtual void	drawDisp(Disp &disp) = 0;
	virtual void	drawButton(Button &button) = 0;
	virtual void	drawScene(Scene &scene) = 0;
	virtual void	display() = 0;
};

#endif /* ILIB_HPP_ */
