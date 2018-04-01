//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Lib loader header
//

#ifndef LIB_LOADER_HPP_
	#define LIB_LOADER_HPP_

#include <iostream>
#include <memory>
#include <dlfcn.h>
#include "IGame.hpp"
#include "ILib.hpp"

class Dlloader {
public:
	Dlloader(std::string path);
	~Dlloader();
	std::unique_ptr<ILib> createLibSym();
	std::unique_ptr<IGame> createGameSym();
private:
	std::string _path;
	void *_open;
};

#endif /* LIB_LOADER_HPP_ */