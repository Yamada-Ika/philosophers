CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror #-g -fsanitize=address #-fsanitize=thread
LDFLAGS		:=
ifeq ($(shell uname), Linux)
	LDFLAGS	+= -pthread  -lpthread
endif

NAME		:= philo
SRCS		:= \
action.c       ft_is.c        ft_strlen.c    make_philo.c   run_thread.c\
arg.c          ft_putstr_fd.c ft_strtoll.c   monitor.c      time.c\
error.c        ft_strcmp.c    get_forks.c    mutex.c        utils.c\
ft_calloc.c    ft_strdup.c    main.c         put_forks.c    wait_thread.c

OBJS		:= $(SRCS:%.c=%.o)
SRCS		:= $(addprefix src/, $(SRCS))
OBJS		:= $(addprefix obj/, $(OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(LDFLAGS) $(OBJS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ -Iinclude

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft empty
