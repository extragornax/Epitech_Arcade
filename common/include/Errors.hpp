//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Errors class header
//

#ifndef ERRORS_HPP_
# define ERRORS_HPP_

# include <string>

class   ArcadeError : public std::exception
{
public:
	// Ctor
	ArcadeError(std::string const &message,
		 std::string const &component = "Unknown");

	// Dtor
	~ArcadeError();

	// Member functions
	const std::string	&getComponent() const noexcept;
	const char		*what() const noexcept override;

protected:
	// Properties

	std::string	_message;
	std::string	_component;
};

class	ConfFileError : public ArcadeError
{
public:
	ConfFileError(std::string const &message,
		  std::string const &component = "Unknown");
};

class   GraphicalInitError : public ArcadeError
{
public:
	GraphicalInitError(std::string const &message,
		  std::string const &component = "Unknown");
};

class   GraphicalInLibError : public ArcadeError
{
public:
	GraphicalInLibError(std::string const &message,
		  std::string const &component = "Unknown");
};

class   GraphicalCleanupError : public ArcadeError
{
public:
	GraphicalCleanupError(std::string const &message,
		  std::string const &component = "Unknown");
};

class   GameCleanupError : public ArcadeError
{
public:
	GameCleanupError(std::string const &message,
		  std::string const &component = "Unknown");
};

class   GameInitError : public ArcadeError
{
public:
	GameInitError(std::string const &message,
		  std::string const &component = "Unknown");
};

class   DLError : public ArcadeError
{
public:
	DLError(std::string const &message,
		  std::string const &component = "Unknown");
};

#endif /* ERRORS_HPP_ */
