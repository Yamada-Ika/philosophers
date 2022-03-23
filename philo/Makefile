# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 19:30:21 by iyamada           #+#    #+#              #
#    Updated: 2022/03/23 23:35:02 by iyamada          ###   ########.fr        #
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
action.c        ft_funcs2.c     init_philo.c    parse.c\
action2.c       ft_funcs3.c     kill_thread.c   put_forks.c\
destroy_mutex.c ft_funcs4.c     main.c          run_thread.c\
destroy_philo.c get_forks.c     monitor.c       usage.c\
error.c         get_forks2.c    mutex.c         utils.c\
ft_funcs.c      init_mutex.c    new_philo.c     wait_thread.c

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
