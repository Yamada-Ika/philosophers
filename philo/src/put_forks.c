/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:42 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/16 00:40:42 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	put_fork_on_leftside(t_philo *philo)
{
	int	left;

	left = get_index(philo->index + 1, philo->num);
	return (mutex_unlock(&(philo->forks[left]), philo->mtx_err, philo->err));
}

static int	put_fork_on_rightside(t_philo *philo)
{
	return (mutex_unlock(&(philo->forks[philo->index]),
			philo->mtx_err, philo->err));
}

static int	put_forks_even_group(t_philo *philo)
{
	if (put_fork_on_leftside(philo) != 0
		|| put_fork_on_rightside(philo) != 0)
	{
		return (1);
	}
	return (0);
}

static int	put_forks_odd_group(t_philo *philo)
{
	if (put_fork_on_rightside(philo) != 0
		|| put_fork_on_leftside(philo) != 0)
	{
		return (1);
	}
	return (0);
}

int	put_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
		return (put_forks_even_group(philo));
	else
		return (put_forks_odd_group(philo));
}
