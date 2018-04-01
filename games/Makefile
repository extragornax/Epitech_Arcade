##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Graphical libs
##

NAMENIBBLER	= lib_arcade_nibbler.so

CC	=	g++

RM	=	rm -f

SRCSNIBBLER	= ./Nibbler/src/Nibbler.cpp	\
			../common/src/Scene.cpp	\
			../common/src/Board.cpp

OBJSNIBBLER	= $(SRCSNIBBLER:.cpp=.o)

CPPFLAGS = -I ./common/include -I ./Nibbler/include -I ../common/include

CPPFLAGS += -W -Wall -Wextra -Wfatal-errors -Werror -fpic

LDFLAGS	= # -shared


all: $(NAMENIBBLER)

$(NAMENIBBLER): $(OBJSNIBBLER)
	$(CC) $(LDFLAGS) -o $(NAMENIBBLER) $(OBJSNIBBLER)

clean:
	$(RM) $(OBJSNIBBLER)

fclean: clean
	$(RM) $(NAMENIBBLER)

re: fclean all

.PHONY: all clean fclean re
