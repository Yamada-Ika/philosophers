/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:28:17 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/24 00:24:23 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_mutex *mtxes, size_t from, size_t to, t_error *err)
{
	size_t	i;

	i = from;
	while (i < to)
	{
		if (pthread_mutex_init(&mtxes[i], NULL) != 0)
		{
			set_err(err, INIT_MTX);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_forks_mutex(t_philo *philos, t_error *err)
{
	return (init_mutexes(philos[1].forks, 1, philos[1].num + 1, err));
}

static int	init_mtxes_mutex(t_philo *philos, t_error *err)
{
	return (init_mutexes(philos[1].mtxes, 0, MTXES_N, err));
}

int	init_mutex(t_philo *philos, t_error *err)
{
	if (init_forks_mutex(philos, err) == FAIL
		|| init_mtxes_mutex(philos, err) == FAIL)
	{
		return (FAIL);
	}
	return (SUCCESS);
}
