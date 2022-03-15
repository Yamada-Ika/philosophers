/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:24 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:29:24 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_fork_on_leftside(t_philo *philo)
{
	int	left;

	left = get_index(philo->index + 1, philo->philo_number);
	if (mutex_lock(&philo->forks[left], philo->mtx_err, philo->err) != 0
		|| print_action(philo, "has taken a fork") != 0)
	{
		return (1);
	}
	return (0);
}

static int	get_fork_on_rightside(t_philo *philo)
{
	if (mutex_lock(&philo->forks[philo->index], philo->mtx_err, philo->err) != 0
		|| print_action(philo, "has taken a fork") != 0)
	{
		return (1);
	}
	return (0);
}

static int	get_forks_even_group(t_philo *philo)
{
	usleep(100);
	if (get_fork_on_leftside(philo) != 0
		|| get_fork_on_rightside(philo) != 0)
	{
		return (1);
	}
	return (0);
}

static int	get_forks_odd_group(t_philo *philo)
{
	usleep(100);
	if (get_fork_on_rightside(philo) != 0
		|| get_fork_on_leftside(philo) != 0)
	{
		return (1);
	}
	return (0);
}

int	get_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
		return (get_forks_even_group(philo));
	else
		return (get_forks_odd_group(philo));
}
