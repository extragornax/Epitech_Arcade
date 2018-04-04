//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Lib loader
//

#include <dlfcn.h>
#include "lib_open.hpp"
#include "Errors.hpp"

Dlloader::Dlloader(std::string path)
	

Dlloader::~Dlloader()
{
	
}

T *Dlloader::createLibSym()
{
        T *(*create) ();

	*(void **)(&create) = dlsym(_open, "create");
	return create();
}
/*
ILib *Dlloader::createLibSym()
{
	ILib *(*createLib) ();

	*(void **)(&createLib) = dlsym(_open, "createLib");
	return createLib();
}

IGame *Dlloader::createGameSym()
{
        IGame *(*createGame) ();

	*(void **)(&createGame) = dlsym(_open, "createGame");
	return createGame();
}
*/
