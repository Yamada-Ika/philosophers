/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:28:56 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/24 00:24:23 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define UNDEFINED_MSG "error: Undefined error is occured\n"

/**
 * @brief Check if an error has occurred
 *
 */
bool	is_err_occured(t_error *err)
{
	return (*err != NO_ERR);
}

/**
 * @brief Set the error kind
 * 
 */
void	set_err(t_error *err, t_error kind)
{
	*err = kind;
}

static char	*gen_err_msg(t_error kind)
{
	static char	*msg[] = {
		"error: Input more philosophers\n",
		"error: Argument number is 4 or 5\n",
		"error: Argument should be positive\n",
		"error: Argument should be numeric\n",
		"error: FAILd to memory allocate\n",
		"error: FAILd to initialize mutex\n",
		"error: FAILd to destroy mutex\n",
		"error: FAILd to lock mutex\n",
		"error: FAILd to unlock mutex\n",
		"error: FAILd to initialize thread attribute\n",
		"error: FAILd to add thread attribute\n",
		"error: FAILd to create thread\n",
		"error: FAILd to detach thread\n",
		"error: FAILd to join thread\n",
	};

	return (ft_strdup(msg[kind]));
}

static bool	is_undefined_err(t_error kind)
{
	if (
		kind == MORE_PHILO
		|| kind == ARG_NUM
		|| kind == ARG_MINUS
		|| kind == ARG_NUMERIC
		|| kind == NO_MEM
		|| kind == INIT_MTX
		|| kind == DESTROY_MTX
		|| kind == LOCK_MTX
		|| kind == UNLOCK_MTX
		|| kind == INIT_ATTR
		|| kind == ADD_ATTR
		|| kind == CREATE_THREAD
		|| kind == DETACH_PHILO
		|| kind == JOIN_THREAD
	)
	{
		return (false);
	}
	else
		return (true);
}

/**
 * @brief Output error messages to standard error output
 * 
 */
int	print_error(t_error kind)
{
	char	*msg;

	if (is_undefined_err(kind))
	{
		ft_putstr_fd(UNDEFINED_MSG, STDERR_FILENO);
		return (FAIL);
	}
	msg = gen_err_msg(kind);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
	return (FAIL);
}
