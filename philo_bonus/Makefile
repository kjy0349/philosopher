# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeykim <jeykim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 19:37:29 by jeykim            #+#    #+#              #
#    Updated: 2022/11/24 19:53:58 by jeykim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC			= init_bonus.c main_bonus.c philo_bonus.c threadc_bonus.c utils_bonus.c
OBJECT		= ${SRC:.c=.o}
INCS		= .

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCS}

${NAME} : ${OBJECT}
	${CC} ${OBJECT} -o ${NAME}

all : ${NAME}

clean :
	rm -f ${OBJECT}

fclean : clean
	rm -f ${NAME}

re : fclean all

bonus : 
	make all

.PHONY : all clean fclean re .c.o