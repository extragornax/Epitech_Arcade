##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Graphical libs
##

NAMENCURSES	= lib_arcade_ncurses.so

LD	=	ld

RM	=	rm -f

SRCSNCURSES	= ./ncurses/src/LNcurses.cpp

OBJSNCURSES	= $(SRCSNCURSES:.cpp=.o)

CPPFLAGS = -I ./common/include -I ./ncurses/include -I ../common/include

CPPFLAGS += -W -Wall -Wextra

LDFLAGS	= -shared -fPIC


all: $(NAMENCURSES)

$(NAMENCURSES): $(OBJSNCURSES)
	 $(LD) $(LDFLAGS) -o $(NAMENCURSES) $(OBJSNCURSES)

clean:
	$(RM) $(OBJSNCURSES)

fclean: clean
	$(RM) $(NAMENCURSES)

re: fclean all

.PHONY: all clean fclean re
