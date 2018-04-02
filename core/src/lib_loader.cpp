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
	: _path(path)
{
	char *error = nullptr;

	_open = dlopen(_path.data(), RTLD_LAZY);
	error = dlerror();
	if (error) {
		std::cout << "ERROR " << error << std::endl;
		throw new DLError("Error in loading " + _path + " lib", "LibLoader");
	}
}

Dlloader::~Dlloader()
{
	dlclose(_open);
}

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
