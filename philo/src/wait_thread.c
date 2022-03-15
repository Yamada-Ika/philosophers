/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:30:07 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:30:08 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Wait for the philosophers to finish their meal
 *
 */
int	wait_philo(t_philo **philo, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_join((*philo)[i].philo_id, NULL) != 0)
		{
			set_err(err, JOIN_THREAD);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Wait for the philosopher to finish monitoring
 * 
 */
int	wait_monitor(t_philo **philo, t_error *err)
{
	if (pthread_join((*philo)[1].monitor_id, NULL) != 0)
	{
		set_err(err, JOIN_THREAD);
		return (1);
	}
	return (0);
}
