# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorion- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 17:10:22 by amorion-          #+#    #+#              #
#    Updated: 2021/09/12 17:10:24 by amorion-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = join.c main.c paths.c parse.c split.c

OBJS = ${SRCS:.c=.o}

NAME = pipex

.c.o:
	@gcc -Wall -Werror -Wextra -c $< -o ${<:.c=.o}

all: ${NAME}

norm:
	norminette ${SRCS}

${NAME}: ${OBJS}
	@echo "pipex generated"
	@gcc -Wall -Werror -Wextra ${OBJS} -o ${NAME}
clean:
	@echo ".o files removed"
	@rm -rf ${OBJS}

fclean: clean
	@echo "pipex removed"
	@rm -rf ${NAME}
re: fclean all