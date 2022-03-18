/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:28:56 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/19 01:59:56 by iyamada          ###   ########.fr       */
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

static char	*get_err_msg(t_error kind)
{
	static char	*msg[] = {
		"error: Input more philosophers\n",
		"error: Argument number is 4 or 5\n",
		"error: Argument should be positive\n",
		"error: Argument should be numeric\n",
		"error: Failed to memory allocate\n",
		"error: Failed to initialize mutex\n",
		"error: Failed to destroy mutex\n",
		"error: Failed to lock mutex\n",
		"error: Failed to unlock mutex\n",
		"error: Failed to initialize thread attribute\n",
		"error: Failed to add thread attribute\n",
		"error: Failed to create thread\n",
		"error: Failed to detach thread\n",
		"error: Failed to join thread\n",
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
void	print_error(t_error kind)
{
	char	*msg;

	if (is_undefined_err(kind))
		return (ft_putstr_fd(UNDEFINED_MSG, STDERR_FILENO));
	msg = get_err_msg(kind);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}
