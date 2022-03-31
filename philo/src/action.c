/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:28:49 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/30 16:34:36 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	update_last_mealtime(t_philo *philo);
int	incre_full_philo(t_philo *philo);
int	still_hungry(t_philo *philo);

static int	philo_think(t_philo *philo)
{
	return (print_action(philo, "is thinking"));
}

static int	philo_sleep(t_philo *philo)
{
	if (put_forks(philo) == FAIL
		|| print_action(philo, "is sleeping") == FAIL
		|| my_msleep(philo, philo->time_to_sleep) == FAIL)
	{
		return (FAIL);
	}
	return (SUCCESS);
}

static int	incre_eat_count(t_philo *philo)
{
	philo->eat_count++;
	if (still_hungry(philo))
	{
		philo->is_full = true;
		return (incre_full_philo(philo));
	}
	return (SUCCESS);
}

static int	philo_eat(t_philo *philo)
{
	if (get_forks(philo) == FAIL
		|| print_action(philo, "is eating") == FAIL
		|| update_last_mealtime(philo) == FAIL
		|| my_msleep(philo, philo->time_to_eat) == FAIL
		|| incre_eat_count(philo) == FAIL)
	{
		return (FAIL);
	}
	return (SUCCESS);
}

void	*do_action(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	if (update_last_mealtime(philo) == FAIL)
		return (NULL);
	while (true)
	{
		if (philo_eat(philo) == FAIL
			|| philo_sleep(philo) == FAIL
			|| philo_think(philo) == FAIL)
		{
			put_forks(philo);
			return (NULL);
		}
	}
	return (NULL);
}
