CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror #-g -fsanitize=address
NAME		:= philo
SRCS		:= action.c fork.c   main.c   utils.c
OBJS		:= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(COPTS) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft empty
