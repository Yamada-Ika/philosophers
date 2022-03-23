/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:34 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 21:31:25 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_philo *philo)
{
	bool	res;

	mutex_lock(&philo->mtxs[TIME], &philo->mtxs[ERR], philo->err);
	res = get_timestamp() - philo->last_meal_time > philo->time_to_die;
	mutex_unlock(&philo->mtxs[TIME], &philo->mtxs[ERR], philo->err);
	return (res);
}

static bool	is_end_dinner(t_philo *philo)
{
	bool	res;

	mutex_lock(&philo->mtxs[COUNT], &philo->mtxs[ERR], philo->err);
	res = philo->should_count_eat
		&& *(philo->full_num) >= philo->num;
	mutex_unlock(&philo->mtxs[COUNT], &philo->mtxs[ERR], philo->err);
	return (res);
}

static bool	is_err_occured_while_dinner(t_philo *philo)
{
	bool	res;

	mutex_lock(&philo->mtxs[ERR], &philo->mtxs[ERR], philo->err);
	res = is_err_occured(philo->err);
	mutex_unlock(&philo->mtxs[ERR], &philo->mtxs[ERR], philo->err);
	return (res);
}

void	set_end_dinner_flag(t_philo *philo)
{
	mutex_lock(&philo->mtxs[STATE], &philo->mtxs[ERR], philo->err);
	*(philo->is_end) = true;
	mutex_unlock(&philo->mtxs[STATE], &philo->mtxs[ERR], philo->err);
}

void	*monitor(void *argp)
{
	t_philo	*philo;
	size_t	i;
	size_t	philo_num;

	philo = (t_philo *)argp;
	philo_num = philo[1].num;
	i = 1;
	while (true)
	{
		if (i >= philo_num)
			i = 1;
		if (is_dead(&philo[i]))
			break ;
		if (is_err_occured_while_dinner(&philo[i])
			|| is_end_dinner(&philo[i]))
		{
			set_end_dinner_flag(&philo[i]);
			return (NULL);
		}
		i++;
	}
	print_action(&philo[i], "died");
	set_end_dinner_flag(&philo[i]);
	return (NULL);
}
