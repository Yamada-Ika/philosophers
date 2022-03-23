/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:34 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 23:29:21 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_philo *philo)
{
	bool	res;

	mutex_lock(&philo->mtxes[TIME], &philo->mtxes[ERR], philo->err);
	res = get_timestamp() - philo->last_meal_time > philo->time_to_die;
	mutex_unlock(&philo->mtxes[TIME], &philo->mtxes[ERR], philo->err);
	return (res);
}

static bool	is_end_dinner(t_philo *philo)
{
	bool	res;

	mutex_lock(&philo->mtxes[COUNT], &philo->mtxes[ERR], philo->err);
	res = philo->should_count_eat
		&& *(philo->full_num) >= philo->num;
	mutex_unlock(&philo->mtxes[COUNT], &philo->mtxes[ERR], philo->err);
	return (res);
}

static bool	is_err_occured_while_dinner(t_philo *philo)
{
	bool	res;

	mutex_lock(&philo->mtxes[ERR], &philo->mtxes[ERR], philo->err);
	res = is_err_occured(philo->err);
	mutex_unlock(&philo->mtxes[ERR], &philo->mtxes[ERR], philo->err);
	return (res);
}

void	set_end_dinner_flag(t_philo *philo)
{
	mutex_lock(&philo->mtxes[STATE], &philo->mtxes[ERR], philo->err);
	*(philo->is_end) = true;
	mutex_unlock(&philo->mtxes[STATE], &philo->mtxes[ERR], philo->err);
}

void	*monitor(void *argp)
{
	t_philo	*philos;
	size_t	i;
	size_t	philo_num;

	philos = (t_philo *)argp;
	philo_num = philos[1].num;
	i = 1;
	while (true)
	{
		if (i >= philo_num)
			i = 1;
		if (is_dead(&philos[i]))
			break ;
		if (is_err_occured_while_dinner(&philos[i])
			|| is_end_dinner(&philos[i]))
		{
			set_end_dinner_flag(&philos[i]);
			return (NULL);
		}
		i++;
	}
	print_action(&philos[i], "died");
	set_end_dinner_flag(&philos[i]);
	return (NULL);
}
