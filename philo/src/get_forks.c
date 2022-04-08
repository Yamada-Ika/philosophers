/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:24 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/08 09:28:23 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_eat_alone(t_philo *philo);
void	wait_for_death(t_philo *philo);

static int	get_fork_on_leftside(t_philo *p)
{
	int	left;

	left = get_index(p, p->index + 1);
	if (mutex_lock(&p->forks[left], &p->mtxes[ERR], p->err) != 0)
		return (FAIL);
	p->is_hold_on_left = true;
	if (print_action(p, "has taken a fork") != 0)
		return (FAIL);
	return (SUCCESS);
}

static int	get_fork_on_rightside(t_philo *p)
{
	if (mutex_lock(&p->forks[p->index], &p->mtxes[ERR], p->err) != 0)
		return (FAIL);
	p->is_hold_on_right = true;
	if (print_action(p, "has taken a fork") != 0)
		return (FAIL);
	return (SUCCESS);
}

static int	get_forks_even_group(t_philo *philo)
{
	if (get_fork_on_leftside(philo) == FAIL
		|| get_fork_on_rightside(philo) == FAIL)
	{
		return (FAIL);
	}
	return (SUCCESS);
}

#define MOMENT 200

static int	get_forks_odd_group(t_philo *philo)
{
	if (get_fork_on_rightside(philo) == FAIL
		|| get_fork_on_leftside(philo) == FAIL)
	{
		return (FAIL);
	}
	return (SUCCESS);
}

int	get_forks(t_philo *philo)
{
	if (is_eat_alone(philo))
	{
		get_fork_on_rightside(philo);
		wait_for_death(philo);
		return (SUCCESS);
	}
	my_usleep(MOMENT);
	if (philo->index % 2 == 0)
		return (get_forks_even_group(philo));
	else
		return (get_forks_odd_group(philo));
}
