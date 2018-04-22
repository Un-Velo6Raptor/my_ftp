##
## EPITECH PROJECT, 2018
## my_ftp
## File description:
## Created by martin.januario@epitech.eu
##

SRC		=	src/main.c				\
			src/check_arg.c				\
			src/basics/str_to_wordtab.c		\
			src/basics/tablen.c			\
			src/basics/free_tab.c			\
			src/init/init_server.c			\
			src/init/init_manage_command.c		\
			src/server/server.c			\
			src/server/error_server.c		\
			src/server/print_client.c		\
			src/server/manage_list_client.c		\
			src/command/manage_command.c		\
			src/command/user.c			\
			src/command/pass.c			\
			src/command/quit.c			\
			src/command/noop.c			\
			src/command/help.c			\
			src/command/cwd.c			\

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
