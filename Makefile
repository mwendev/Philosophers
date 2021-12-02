# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 16:41:11 by mwen              #+#    #+#              #
#    Updated: 2021/11/29 02:22:26 by mwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
CC 				=	gcc
FLAGS			=	-Wall -Werror -Wextra -g
RM				=	rm -rf

SRCS_LIST		=	main.c init.c utils.c simulate.c

OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS_DIR		=	obj/
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

GREEN			=	\033[0;32m
RED				=	\033[0;31m
RESET			=	\033[0m

.PHONY:			all clean fclean re

all:			$(NAME)

$(NAME):		$(OBJS_DIR) $(OBJS)
				@$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lpthread
				@echo "Please enter: ./philo number_philo time_die\
 time_eat time_sleep [times_must_eat]"

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o:	%.c 
				@$(CC) $(FLAGS) -c $< -o $@

clean:
				@$(RM) $(OBJS_DIR)
				@echo "$(RED)cleaned$(RESET)"

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all
