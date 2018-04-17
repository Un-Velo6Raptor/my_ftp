##
## EPITECH PROJECT, 2018
## my_ftp
## File description:
## Created by martin.januario@epitech.eu
##

SRC		=	src/main.c				\
			src/check_arg.c				\

OBJ		=	$(SRC:.c=.o)

CFLAGS		=	-w -Wall -Wextra -Werror -I include/

NAME		=	server

all:			$(NAME)

$(NAME):		$(OBJ)
			gcc -o $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)

debug:			CFLAGS += -ggdb3

debug:			re

re:			fclean all

.PHONY:			all clean fclean debug re
