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

	_open = dlopen(_path.c_str(), RTLD_LAZY);
	if ((error = dlerror()) != NULL)
		throw new DLError("Error in loading " + _path + " lib", "LibLoader");
}

Dlloader::~Dlloader()
{
	dlclose(_open);
}

std::unique_ptr<ILib> Dlloader::createLibSym()
{
	std::unique_ptr<ILib> (*createLib) ();

	*(void **)(&createLib) = dlsym(_open, "createLib");
	return createLib();
}

std::unique_ptr<IGame> Dlloader::createGameSym()
{
	std::unique_ptr<IGame> (*createGame) ();

	*(void **)(&createGame) = dlsym(_open, "createLib");
	return createGame();
}
