/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:46 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/19 03:24:12 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_odd_group(t_philo **philo, t_attr *attr, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].num + 1)
	{
		if (pthread_create(&((*philo)[i].philo_id), attr,
			do_action, &((*philo)[i])) != 0)
		{
			set_err(err, CREATE_THREAD);
			return (1);
		}
		i += 2;
	}
	return (0);
}

static int	create_even_group(t_philo **philo, t_attr *attr, t_error *err)
{
	size_t	i;

	i = 2;
	while (i < (*philo)[1].num + 1)
	{
		if (pthread_create(&((*philo)[i].philo_id), attr,
			do_action, &((*philo)[i])) != 0)
		{
			set_err(err, CREATE_THREAD);
			return (1);
		}
		i += 2;
	}
	return (0);
}

static void	wait_a_moment(void)
{
	usleep(100);
}

/**
 * @brief Created multiple threads to feed philosophers in parallel
 * @details The philosophers are divided into even and odd groups,
 *          and the odd group threads are run first.
 */
int	run_philo_thread(t_philo **philo, t_error *err)
{
	if (create_odd_group(philo, NULL, err) != 0)
	{
		kill_thread(&((*philo)[1]));
		return (1);
	}
	wait_a_moment();
	if (create_even_group(philo, NULL, err) != 0)
	{
		kill_thread(&((*philo)[2]));
		return (1);
	}
	return (0);
}

/**
 * @brief Monitor the state of the philosopher
 * @details There is only one thread on the monitor
 */
int	run_monitor_thread(t_philo **philo, t_error *err)
{
	if (pthread_create(&((*philo)[1].monitor_id), NULL,
		monitor, ((*philo))) != 0)
	{
		kill_thread(&((*philo)[1]));
		set_err(err, CREATE_THREAD);
		return (1);
	}
	return (0);
}
