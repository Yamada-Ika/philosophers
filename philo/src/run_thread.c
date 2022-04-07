/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:46 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/07 10:15:50 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_thread_helper(t_philo *philos, t_error *err, size_t from)
{
	while (from < philos[1].num + 1)
	{
		if (pthread_create(&philos[from].philo_id,
				NULL, do_action, &philos[from]) != 0)
		{
			set_err(err, CREATE_THREAD);
			return (FAIL);
		}
		from += 2;
	}
	return (SUCCESS);
}

static int	create_odd_group(t_philo *philos, t_error *err)
{
	return (create_thread_helper(philos, err, 1));
}

static int	create_even_group(t_philo *philos, t_error *err)
{
	return (create_thread_helper(philos, err, 2));
}

#define MOMENT 200

/**
 * @brief Created multiple threads to feed philosophers in parallel
 * @details The philosophers are divided into even and odd groups,
 *          and the odd group threads are run first.
 */
int	run_philo_thread(t_philo *philos, t_error *err)
{
	if (create_odd_group(philos, err) == FAIL)
	{
		kill_thread(&philos[1]);
		return (FAIL);
	}
	my_usleep(MOMENT);
	if (create_even_group(philos, err) == FAIL)
	{
		kill_thread(&philos[2]);
		return (FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief Monitor the state of the philosopher
 * @details There is only one thread on the monitor
 */
int	run_monitor_thread(t_philo *philos, t_error *err)
{
	if (pthread_create(&philos[1].monitor_id, NULL, monitor, philos) != 0)
	{
		kill_thread(&philos[1]);
		set_err(err, CREATE_THREAD);
		return (FAIL);
	}
	return (SUCCESS);
}
