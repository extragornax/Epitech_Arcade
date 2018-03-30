//
// EPITECH PROJECT, 2018
// nanotekspice
// File description:
// Errors class
//

#include "Errors.hpp"

ArcadeError::ArcadeError(std::string const &message, std::string const &component)
	: _message(message), _component(component)
{

}

ArcadeError::~ArcadeError()
{

}

const std::string	&ArcadeError::getComponent() const noexcept
{
	return _message;
}

const char	*ArcadeError::what() const noexcept
{
	return _message.data();
}

ConfFileError::ConfFileError(std::string const &message, std::string const &component)
	: ArcadeError(message, component)
{

}

GraphicalInitError::GraphicalInitError(std::string const &message, std::string const &component)
	: ArcadeError(message, component)
{

}

GraphicalInLibError::GraphicalInLibError(std::string const &message, std::string const &component)
	: ArcadeError(message, component)
{

}

GraphicalCleanupError::GraphicalCleanupError(std::string const &message, std::string const &component)
	: ArcadeError(message, component)
{

}

GameCleanupError::GameCleanupError(std::string const &message, std::string const &component)
	: ArcadeError(message, component)
{

}

GameInitError::GameInitError(std::string const &message, std::string const &component)
	: ArcadeError(message, component)
{

}

DLError::DLError(std::string const &message, std::string const &component)
	: ArcadeError(message, component)
{

}
