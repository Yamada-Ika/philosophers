/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:31:00 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/07 10:15:23 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutexes(t_mutex *mtxs, size_t from, size_t to, t_error *err)
{
	size_t	i;

	i = from;
	while (i < to)
	{
		if (pthread_mutex_destroy(&mtxs[i]) != 0)
		{
			set_err(err, DESTROY_MTX);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

static int	destroy_forks_mutex(t_philo *philos, t_error *err)
{
	return (destroy_mutexes(philos[1].forks, 1, philos[1].num + 1, err));
}

static int	destroy_mtxes_mutex(t_philo *philos, t_error *err)
{
	return (destroy_mutexes(philos[1].mtxes, 0, MTXES_N, err));
}

/**
 * @brief Destroy mutex
 * @details To avoid errors with valgrind
 * 
 */
int	destroy_mutex(t_philo *philos, t_error *err)
{
	size_t	i;

	if (destroy_forks_mutex(philos, err) == FAIL
		|| destroy_mtxes_mutex(philos, err) == FAIL)
	{
		return (FAIL);
	}
	i = 1;
	while (i < philos[1].num + 1)
	{
		if (pthread_mutex_destroy(&philos[i].time_mtx) != 0)
		{
			set_err(err, DESTROY_MTX);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}
