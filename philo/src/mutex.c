/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:36 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:29:37 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < philo[1].philo_number + 1)
	{
		if (pthread_mutex_init(&philo[1].forks[i], NULL) != 0)
		{
			set_err(err, INIT_MTX);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(philo[1].log, NULL) != 0
		|| pthread_mutex_init(philo[1].state, NULL) != 0
		|| pthread_mutex_init(philo[1].count, NULL) != 0
		|| pthread_mutex_init(philo[1].time, NULL) != 0
		|| pthread_mutex_init(philo[1].mtx_err, NULL) != 0)
	{
		set_err(err, INIT_MTX);
		return (1);
	}
	return (0);
}

/**
 * @brief Destroy mutex
 * @details To avoid errors with valgrind
 * 
 */
int	destroy_mutex(t_philo **philo, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_mutex_destroy(&(*philo)[1].forks[i]) != 0)
		{
			set_err(err, DESTROY_MTX);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_destroy((*philo)[1].log) != 0
		|| pthread_mutex_destroy((*philo)[1].state) != 0
		|| pthread_mutex_destroy((*philo)[1].count) != 0
		|| pthread_mutex_destroy((*philo)[1].time) != 0
		|| pthread_mutex_destroy((*philo)[1].mtx_err) != 0)
	{
		set_err(err, DESTROY_MTX);
		return (1);
	}
	return (0);
}

int	mutex_lock(t_mutex *mtx, t_mutex *mtx_err, t_error *err)
{
	if (pthread_mutex_lock(mtx) != 0)
	{
		pthread_mutex_lock(mtx_err);
		set_err(err, LOCK_MTX);
		pthread_mutex_unlock(mtx_err);
		return (1);
	}
	return (0);
}

int	mutex_unlock(t_mutex *mtx, t_mutex *mtx_err, t_error *err)
{
	if (pthread_mutex_unlock(mtx) != 0)
	{
		pthread_mutex_lock(mtx_err);
		set_err(err, UNLOCK_MTX);
		pthread_mutex_unlock(mtx_err);
		return (1);
	}
	return (0);
}
