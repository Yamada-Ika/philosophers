/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:28:49 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:28:50 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	update_mealtime(t_philo *philo);
int	incre_full_philo(t_philo *philo);
int	still_hungry(t_philo *philo);

static int	philo_think(t_philo *philo)
{
	return (print_action(philo, "is thinking"));
}

static int	philo_sleep(t_philo *philo)
{
	if (put_forks(philo) != 0
		|| print_action(philo, "is sleeping") != 0)
		return (1);
	my_msleep(philo->time_to_sleep);
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	if (get_forks(philo) != 0
		|| print_action(philo, "is eating") != 0)
	{
		put_forks(philo);
		return (1);
	}
	my_msleep(philo->time_to_eat);
	if (update_mealtime(philo) != 0)
		return (1);
	philo->eat_count++;
	if (still_hungry(philo))
	{
		philo->is_full = true;
		return (incre_full_philo(philo));
	}
	return (0);
}

void	*do_action(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	if (update_mealtime(philo) != 0)
		return (NULL);
	while (true)
	{
		if (philo_eat(philo) != 0
			|| philo_sleep(philo) != 0
			|| philo_think(philo) != 0)
		{
			return (NULL);
		}
	}
	return (NULL);
}
