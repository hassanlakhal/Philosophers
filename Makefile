# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlakhal- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 22:13:31 by hlakhal-          #+#    #+#              #
#    Updated: 2023/03/12 15:32:32 by hlakhal-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =  ft_atoi.c philo.c utils.c   utils1.c

OBJ = $(SRCS:.c=.o)

CC		= cc

CFLAGS = -Wall -Wextra -Werror

philo:$(OBJ)
		$(CC) $(CFLAGS) -fsanitize=thread -g3 $(OBJ)  -o philo

all:${NAME}

clean:
		rm -f ${OBJ}

fclean:	clean
		rm -f ${NAME}

re:		fclean all
