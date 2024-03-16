# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalhamm <abalhamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 18:02:21 by abalhamm          #+#    #+#              #
#    Updated: 2023/08/15 18:27:49 by abalhamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	philo.c need_utils.c in_the_game.c routine.c \
					p_mutex.c need_utils_ext.c
					
NAME			= philo

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -pthread -I. -g

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus
