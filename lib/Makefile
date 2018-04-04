##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Graphical libs
##

NAMENCURSES	= lib_arcade_ncurses.so

NAMESFML	= lib_arcade_sfml.so

NAMESDL		= lib_arcade_sdl.so

CC	=	g++

RM	=	rm -f

SRCSNCURSES	= ./ncurses/src/LNcurses.cpp	\
		  ../common/src/Errors.cpp	\
		  ../common/src/Board.cpp	\
		  ../common/src/Scene.cpp


OBJSNCURSES	= $(SRCSNCURSES:.cpp=.o)

SRCSSFML	= ./SFML/src/Lsfml.cpp		\
		  ../common/src/Board.cpp	\
		  ../common/src/Scene.cpp	\
		  ../common/src/Errors.cpp

OBJSSFML		= $(SRCSSFML:.cpp=.o)

SRCSSDL		= ./SDL/src/Lsdl.cpp		\
		  ../common/src/Board.cpp	\
		  ../common/src/Scene.cpp	\
		  ../common/src/Errors.cpp

OBJSSDL		= $(SRCSSDL:.cpp=.o)

CPPFLAGS = -I ./common/include -I ./ncurses/include -I ../common/include -I ./SFML/include -I ./SDL/include

CPPFLAGS += -W -Wall -Wextra -fPIC

LDFLAGS	= -shared


all: $(NAMESFML) $(NAMENCURSES) #$(NAMESDL)

$(NAMENCURSES): $(OBJSNCURSES)
	 $(CC) $(LDFLAGS) -o $(NAMENCURSES) $(OBJSNCURSES) -lncurses

$(NAMESFML): $(OBJSSFML)
	$(CC) $(OBJSSFML) -o $(NAMESFML) $(LDFLAGS) -lsfml-system -lsfml-window -lsfml-network -lsfml-graphics -lsfml-audio

$(NAMESDL): $(OBJSSDL)
	 $(CC) $(LDFLAGS) -o $(NAMESDL) $(OBJSSDL) -lSDL

clean:
	$(RM) $(OBJSNCURSES)
	$(RM) $(OBJSSFML)
	$(RM) $(OBJSSDL)

fclean: clean
	$(RM) $(NAMENCURSES)
	$(RM) $(NAMESFML)
	$(RM) $(NAMESDL)

re: fclean all

.PHONY: all clean fclean re

# gcc -c -Wall -Werror -fpic one.c
