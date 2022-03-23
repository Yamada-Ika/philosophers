/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:42 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 21:36:36 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	put_fork_on_leftside(t_philo *philo)
{
	int	left;

	if (!philo->is_hold_on_left)
		return (SUCCESS);
	left = get_index(philo->index + 1, philo->num);
	if (mutex_unlock(&(philo->forks[left]),
			&philo->mtxs[ERR], philo->err) == FAILE)
	{
		return (FAILE);
	}
	philo->is_hold_on_left = false;
	return (SUCCESS);
}

static int	put_fork_on_rightside(t_philo *philo)
{
	if (!philo->is_hold_on_right)
		return (SUCCESS);
	if (mutex_unlock(&(philo->forks[philo->index]),
			&philo->mtxs[ERR], philo->err) == FAILE)
	{
		return (FAILE);
	}
	philo->is_hold_on_right = false;
	return (SUCCESS);
}

static int	put_forks_even_group(t_philo *philo)
{
	if (put_fork_on_leftside(philo) == FAILE
		|| put_fork_on_rightside(philo) == FAILE)
	{
		return (FAILE);
	}
	return (SUCCESS);
}

static int	put_forks_odd_group(t_philo *philo)
{
	if (put_fork_on_rightside(philo) == FAILE
		|| put_fork_on_leftside(philo) == FAILE)
	{
		return (FAILE);
	}
	return (SUCCESS);
}

int	put_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
		return (put_forks_even_group(philo));
	else
		return (put_forks_odd_group(philo));
}
