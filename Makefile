NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

LIBFT = ./libft/libft.a

SRCS = srcs/pipex.c \
	srcs/processes.c \
	srcs/commands.c \
	srcs/utils.c

OBJS = $(SRCS:.c=.o)

all:	$(LIBFT) $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "\n\tCompilation completed successfully!\n"

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
