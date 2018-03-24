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
	_open = dlopen(_path, RTLD_LAZY);
	if ((error = dlerror()) != NULL)
		throw new DLError::DLError("Error in loading " + _path + " lib");
}

Dlloader::~Dlloader()
{
	char	*error = NULL;

	dlerror();
	dlclose(_name);
	if ((error = dlerror()) != NULL)
		throw new DLError::DLError("Error in closing " + _path + " lib");
}

//entrypoint ? What

std::unique_ptr<T>	&getInstance(std::string entryPoint) noexcept
{
	// return quoi ? Oo
}
