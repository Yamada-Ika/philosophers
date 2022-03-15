/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 00:38:04 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/16 00:40:42 by iyamada          ###   ########.fr       */
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
void	wait_for_death(t_philo *philo)
{
	my_msleep(philo->time_to_die);
	my_msleep(philo->time_to_die);
}
