##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Graphical libs
##

NAMENIBBLER	= lib_arcade_nibbler.so

NAMEPACMAN	= lib_arcade_pacman.so	

CC	=	g++ -g3

RM	=	rm -f

SRCSNIBBLER	= ./Nibbler/src/Nibbler.cpp	\
			../common/src/Scene.cpp	\
			../common/src/Board.cpp

SRCSPACMAN	= ./Pacman/src/Pacman.cpp	\
			../common/src/Scene.cpp	\
			../common/src/Board.cpp

OBJSNIBBLER	= $(SRCSNIBBLER:.cpp=.o)

OBJSPACMAN	= $(SRCSPACMAN:.cpp=.o)

CPPFLAGS = -I ./common/include -I ./Nibbler/include -I ../common/include -I ./Pacman/include

CPPFLAGS += -W -Wall -Wextra -Wfatal-errors -Werror -fpic

LDFLAGS	= -shared

all: $(NAMENIBBLER) $(NAMEPACMAN)

$(NAMENIBBLER): $(OBJSNIBBLER)
	$(CC) $(LDFLAGS) -o $(NAMENIBBLER) $(OBJSNIBBLER)

$(NAMEPACMAN): $(OBJSPACMAN)
	$(CC) $(LDFLAGS) -o $(NAMEPACMAN) $(OBJSPACMAN)

clean:
	$(RM) $(OBJSNIBBLER)
	$(RM) $(OBJSPACMAN)

fclean: clean
	$(RM) $(NAMENIBBLER)
	$(RM) $(NAMEPACMAN)

re: fclean all

.PHONY: all clean fclean re
