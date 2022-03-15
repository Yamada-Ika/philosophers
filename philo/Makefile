# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 19:30:21 by iyamada           #+#    #+#              #
#    Updated: 2022/03/16 01:01:43 by iyamada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror #-g -fsanitize=address #-fsanitize=thread
LDFLAGS		:=
ifeq ($(shell uname), Linux)
	LDFLAGS	+= -pthread  -lpthread
endif

NAME		:= philo
SRCS		:= \
action.c       ft_putstr_fd.c get_forks.c    monitor.c      utils.c\
action2.c      ft_strcmp.c    get_forks2.c   mutex.c        wait_thread.c\
error.c        ft_strdup.c    main.c         parse.c\
ft_calloc.c    ft_strlen.c    make_philo.c   put_forks.c\
ft_is.c        ft_strtoll.c   make_philo2.c  run_thread.c

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
