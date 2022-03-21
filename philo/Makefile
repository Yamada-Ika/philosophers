# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 19:30:21 by iyamada           #+#    #+#              #
#    Updated: 2022/03/21 19:16:25 by iyamada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror #-g -fsanitize=thread #-fsanitize=address
LDFLAGS		:=
ifeq ($(shell uname), Linux)
	LDFLAGS	+= -pthread  -lpthread
endif

NAME		:= philo
SRCS		:= \
action.c        ft_strlen.c     new_philo.c\
action2.c       ft_strtoll.c    parse.c\
destroy_philo.c get_forks.c     put_forks.c\
error.c         get_forks2.c    run_thread.c\
ft_calloc.c     init_philo.c    usage.c\
ft_is.c         kill_thread.c   utils.c\
ft_putstr_fd.c  main.c          wait_thread.c\
ft_strcmp.c     monitor.c\
ft_strdup.c     mutex.c

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

.PHONY: all clean fclean re
