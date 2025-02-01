NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

RM = rm -f

SRCS = pipex.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY:	all clean fclean re

