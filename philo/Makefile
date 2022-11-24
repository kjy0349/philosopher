# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 19:37:29 by jeykim            #+#    #+#              #
#    Updated: 2022/11/24 19:55:19 by jeykim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC			= init.c main.c philo.c threadc.c utils.c
OBJECT		= ${SRC:.c=.o}
INC			= .

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INC}

${NAME} : ${OBJECT}
	${CC} ${OBJECT} -o ${NAME}

all : ${NAME}

clean :
	rm -f ${OBJECT}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re .c.o