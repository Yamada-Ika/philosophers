/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:38:04 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/24 00:24:23 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_eat_alone(t_philo *philo)
{
	return (philo->num == 1);
}

/**
 * @brief Wait until the philosopher dies.
 * @details Call wait function twice to avoid overflow
 */
int	wait_for_death(t_philo *philo)
{
	if (my_msleep(philo, philo->time_to_die) != 0
		|| my_msleep(philo, 10) != 0)
	{
		return (FAIL);
	}
	return (SUCCESS);
}
