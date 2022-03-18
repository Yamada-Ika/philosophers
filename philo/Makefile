# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 19:30:21 by iyamada           #+#    #+#              #
#    Updated: 2022/03/19 03:25:20 by iyamada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror #-g -fsanitize=address #-fsanitize=thread
LDFLAGS		:=
ifeq ($(shell uname), Linux)
	LDFLAGS	+= -pthread  -lpthread
endif

NAME		:= philo
SRCS		:= \
action.c       ft_is.c        ft_strlen.c    kill_thread.c  monitor.c      run_thread.c\
action2.c      ft_putstr_fd.c ft_strtoll.c   main.c         mutex.c        utils.c\
error.c        ft_strcmp.c    get_forks.c    make_philo.c   parse.c        wait_thread.c\
ft_calloc.c    ft_strdup.c    get_forks2.c   make_philo2.c  put_forks.c

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
