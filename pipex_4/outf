# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 20:51:59 by dsatge            #+#    #+#              #
#    Updated: 2024/09/26 20:52:10 by dsatge           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

FILES = main.c

SRC_FILES = valid_input.c\
	path.c\

FLAGS = -Wall -Wextra -Werror -I includes/ -g

LIB = libft/libft.a printf/libftprintf.a

DEPS = $(addprefix lib/,${LIB:%.c=%.o})

SRC = $(addprefix sources/,${SRC_FILES})

all: ${NAME}

${NAME} : ${FILES} ${SRC}
	make -C lib/libft
	make -C lib/printf
	cc ${FLAGS} ${FILES} ${SRC} -o ${NAME} ${DEPS}

clean:
	make -C lib/libft clean
	make -C lib/printf clean

fclean: clean
	rm -rf ${NAME}

re: fclean all
	make -C lib/libft re
	make -C lib/printf re

.PHONY: all clean fclean re