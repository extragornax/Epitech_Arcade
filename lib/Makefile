##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Graphical libs
##

NAMENCURSES	= lib_arcade_ncurses.so

CC	=	g++

RM	=	rm -f

SRCSNCURSES	= ./ncurses/src/LNcurses.cpp

OBJSNCURSES	= $(SRCSNCURSES:.cpp=.o)

CPPFLAGS = -I ./common/include -I ./ncurses/include -I ../common/include

CPPFLAGS += -W -Wall -Wextra -fPIC -lncurses

LDFLAGS	= -shared


all: $(NAMENCURSES)

$(NAMENCURSES): $(OBJSNCURSES)
	 $(CC) $(LDFLAGS) -o $(NAMENCURSES) $(OBJSNCURSES)

clean:
	$(RM) $(OBJSNCURSES)

fclean: clean
	$(RM) $(NAMENCURSES)

re: fclean all

.PHONY: all clean fclean re

# gcc -c -Wall -Werror -fpic one.c
