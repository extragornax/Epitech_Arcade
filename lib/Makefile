##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Graphical libs
##

NAMENCURSES	= lib_arcade_ncurses.so

NAMESFML	= lib_arcade_sfml.so

CC	=	g++

RM	=	rm -f

SRCSNCURSES	= ./ncurses/src/LNcurses.cpp	\
		  ../common/src/Errors.cpp	\
		  ../common/src/Board.cpp	\
		  ../common/src/Scene.cpp


OBJSNCURSES	= $(SRCSNCURSES:.cpp=.o)

SRCSSFML	= ./SFML/src/Lsfml.cpp		\
		  ../common/src/Board.cpp	\
		  ../common/src/Scene.cpp

OBJSSFML	= $(SRCSSFML:.cpp=.o)

CPPFLAGS = -I ./common/include -I ./ncurses/include -I ../common/include -I ./SFML/include

CPPFLAGS += -W -Wall -Wextra -fPIC

LDFLAGS	= -shared


all: $(NAMENCURSES) #$(NAMESFML)

$(NAMENCURSES): $(OBJSNCURSES)
	 $(CC) $(LDFLAGS) -o $(NAMENCURSES) $(OBJSNCURSES) -lncurses

$(NAMESFML): $(OBJSSFML)
	$(CC) $(LDFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o $(NAMESFML) $(OBJSSFML)

clean:
	$(RM) $(OBJSNCURSES)
	$(RM) $(OBJSSFML)

fclean: clean
	$(RM) $(NAMENCURSES)
	$(RM) $(NAMESFML)

re: fclean all

.PHONY: all clean fclean re

# gcc -c -Wall -Werror -fpic one.c
