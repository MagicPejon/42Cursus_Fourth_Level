# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 15:27:54 by amalbrei          #+#    #+#              #
#    Updated: 2022/10/25 16:05:13 by amalbrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEFAULT	=	\033[0m
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
PURPLE	=	\033[0;35m
CYAN	=	\033[1;36m

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3
RM		=	rm	-rf

SRCS 	=	

all: $(NAME)

%.o: %.c
	@printf "\033[A\033[2K\r$(GREEN)Compiling: "
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇🏇"
	
OBJS	= 	$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(MAKE) all -C libft
	@printf "$(CYAN)\n==========================\n"
	@printf "$(CYAN) PROGRAM CREATED\n"
	@printf "$(CYAN)==========================\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@printf "$(RED)CLEANING PHILO.O FILES\n"
	@$(RM) $(OBJS)

fclean: clean
	@printf "$(RED)CLEANING PHILOSOPHERS PROGRAM\n"
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY = all clean fclean re