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
CPPFLAGS += -W -Wall -Wextra -fPIC

all: $(NAME)
	make all -C lib

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -ldl

clean:
	$(RM) $(OBJS)
	make clean -C lib

fclean: clean
	$(RM) $(NAME)
	make fclean -C lib

re: fclean all

.PHONY: all clean fclean re
