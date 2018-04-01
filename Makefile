##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Core makefile
##

NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./core/src/lib_loader.cpp \
	  ./core/src/main.cpp	    \
	  ./common/src/Errors.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I core/include -I common/include -I games/common/include -I lib/common/include
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -ldl

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
