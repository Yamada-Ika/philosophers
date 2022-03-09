CC			:= cc
CFLAGS		:= -g -fsanitize=thread #-Wall -Wextra -Werror  #-fsanitize=address
NAME		:= philo
SRCS		:= \
action.c  init.c    utils.c\
fork.c    init2.c   monitor.c utils2.c

ifdef DEBUG
	SRCS += main_dbg.c
else
	SRCS += main.c
endif

OBJS		:= $(SRCS:%.c=%.o)
SRCS		:= $(addprefix src/, $(SRCS))
OBJS		:= $(addprefix obj/, $(OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(COPTS) $(OBJS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ -Iinclude

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug:
	make DEBUG=1

.PHONY: all clean fclean re libft empty
