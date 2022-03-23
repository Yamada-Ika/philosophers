/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:36 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 22:54:05 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < philo[1].num + 1)
	{
		if (pthread_mutex_init(&philo[1].forks[i], NULL) != 0)
		{
			set_err(err, INIT_MTX);
			return (FAILE);
		}
		i++;
	}
	i = 0;
	while (i < MTXS_N)
	{
		if (pthread_mutex_init(&philo[1].mtxs[i], NULL) != 0)
		{
			set_err(err, INIT_MTX);
			return (FAILE);
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Destroy mutex
 * @details To avoid errors with valgrind
 * 
 */
int	destroy_mutex(t_philo *philo, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < philo[1].num + 1)
	{
		if (pthread_mutex_destroy(&philo[1].forks[i]) != 0)
		{
			set_err(err, DESTROY_MTX);
			return (FAILE);
		}
		i++;
	}
	i = 0;
	while (i < MTXS_N)
	{
		if (pthread_mutex_init(&philo[1].mtxs[i], NULL) != 0)
		{
			set_err(err, INIT_MTX);
			return (FAILE);
		}
		i++;
	}
	return (SUCCESS);
}

int	mutex_lock(t_mutex *mtx, t_mutex *mtx_err, t_error *err)
{
	if (pthread_mutex_lock(mtx) != 0)
	{
		pthread_mutex_lock(mtx_err);
		set_err(err, LOCK_MTX);
		pthread_mutex_unlock(mtx_err);
		return (FAILE);
	}
	return (SUCCESS);
}

int	mutex_unlock(t_mutex *mtx, t_mutex *mtx_err, t_error *err)
{
	if (pthread_mutex_unlock(mtx) != 0)
	{
		pthread_mutex_lock(mtx_err);
		set_err(err, UNLOCK_MTX);
		pthread_mutex_unlock(mtx_err);
		return (FAILE);
	}
	return (SUCCESS);
}
