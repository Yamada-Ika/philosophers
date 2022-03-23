/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:46 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 22:52:49 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_thread_helper(t_philo *philo, t_error *err, size_t from)
{
	while (from < philo[1].num + 1)
	{
		if (pthread_create(&philo[from].philo_id, NULL,
			do_action, &philo[from]) != 0)
		{
			set_err(err, CREATE_THREAD);
			return (FAILE);
		}
		from += 2;
	}
	return (SUCCESS);
}

static int	create_odd_group(t_philo *philo, t_error *err)
{
	return (create_thread_helper(philo, err, 1));
}

static int	create_even_group(t_philo *philo, t_error *err)
{
	return (create_thread_helper(philo, err, 2));
}

/**
 * @brief Created multiple threads to feed philosophers in parallel
 * @details The philosophers are divided into even and odd groups,
 *          and the odd group threads are run first.
 */
int	run_philo_thread(t_philo *philo, t_error *err)
{
	if (create_odd_group(philo, err) == FAILE)
	{
		kill_thread(&philo[1]);
		return (FAILE);
	}
	usleep(100);
	if (create_even_group(philo, err) == FAILE)
	{
		kill_thread(&philo[2]);
		return (FAILE);
	}
	return (SUCCESS);
}

/**
 * @brief Monitor the state of the philosopher
 * @details There is only one thread on the monitor
 */
int	run_monitor_thread(t_philo *philo, t_error *err)
{
	if (pthread_create(&philo[1].monitor_id, NULL,
		monitor, philo) != 0)
	{
		kill_thread(&philo[1]);
		set_err(err, CREATE_THREAD);
		return (FAILE);
	}
	return (SUCCESS);
}
