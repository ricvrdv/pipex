# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 20:30:01 by rjesus-d          #+#    #+#              #
#    Updated: 2025/02/05 21:39:04 by rjesus-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

LIBFT = ./libft/libfta

SRCS = pipex.c

OBJS = $(SRCS:.c=.o)

all:	$(LIBFT) $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
