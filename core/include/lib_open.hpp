//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Lib loader header
//

#ifndef LIB_LOADER_HPP_
# define LIB_LOADER_HPP_

#include <iostream>
#include <memory>
#include <dlfcn.h>
#include "IGame.hpp"
#include "ILib.hpp"

template <typename T>
class Dlloader {
public:
	Dlloader(std::string path) : _path(path) {
		char *error = nullptr;
			
		_open = dlopen(_path.data(), RTLD_LAZY);
		error = dlerror();
		if (error) {
			std::cout << "ERROR " << error << std::endl;
			throw new DLError("Error in loading " + _path + " lib", "LibLoader");
		}
	};
	
	~Dlloader() {
		dlclose(_open);
	};
	
	T *createSym() {
		T *(*create) ();
		
		*(void **)(&create) = dlsym(_open, "create");
		return create();
	};
//	IGame *createGameSym();
private:
	std::string _path;
	void *_open;
};

#endif /* LIB_LOADER_HPP_ */
