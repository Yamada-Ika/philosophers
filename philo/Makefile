CC			:= cc
CFLAGS		:= -g -fsanitize=address -Wall -Wextra -Werror #-fsanitize=thread
NAME		:= philo
SRCS		:= \
action.c             ft_strdup.c          monitor.c\
arg.c                ft_strlen_s.c        pthread.c\
error.c              ft_strncmp.c         put_forks.c\
ft_isalnum.c         ft_strtoll.c         run_monitor_thread.c\
ft_isalpha.c         get_forks.c          run_philo_thread.c\
ft_isdigit.c         main.c               time.c\
ft_putstr_fd.c       make_mutex.c         utils.c\
ft_strcmp.c          make_philo.c         wait_monitor.c

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
