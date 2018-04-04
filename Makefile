##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Core makefile
##

NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./core/src/main.cpp	    \
	  ./common/src/Errors.cpp
#./core/src/lib_loader.cpp \
	  .

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I core/include -I common/include -I games/common/include -I lib/common/include
CPPFLAGS += -W -Wall -Wextra -fPIC

all: $(NAME)
	make all -C lib
	make all -C games

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -ldl

clean:
	$(RM) $(OBJS)
	make clean -C lib
	make clean -C games

fclean: clean
	$(RM) $(NAME)
	make fclean -C lib
	make fclean -C games

re: fclean all

.PHONY: all clean fclean re
