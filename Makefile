# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 08:01:18 by cleblais          #+#    #+#              #
#    Updated: 2023/02/09 16:04:14 by cleblais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		philo

SRCS		=		main.c routines.c utils_philo.c	mutex_and_struct.c \
					diner.c utils_and_checks.c utils_and_checks2.c

OBJS		= 		$(SRCS:.c=.o)

CC			=		gcc

CFLAGS		=		-Wall -Wextra -Werror -g

RM			= 		rm -f

all			:		$(NAME)

$(NAME)		:		$(OBJS)
					$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
					$(RM) $(OBJS) $(OBJS_BONUS)

fclean		:		clean
					$(RM) $(NAME)

re			:		fclean all
