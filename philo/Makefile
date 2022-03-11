CC			:= cc
CFLAGS		:= #-g -fsanitize=address #-fsanitize=thread #-Wall -Wextra -Werror  #-fsanitize=address
NAME		:= philo
SRCS		:= \
action.c             ft_putstr_fd.c       get_forks.c          run_monitor_thread.c\
arg.c                ft_strcmp.c          main.c               run_philo_thread.c\
error.c              ft_strdup.c          make_mutex.c         time.c\
ft_isalnum.c         ft_strlen_s.c        make_philo.c         utils.c\
ft_isalpha.c         ft_strncmp.c         monitor.c            wait_monitor.c\
ft_isdigit.c         ft_strtoll.c         put_forks.c

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

.PHONY: all clean fclean re libft empty
