/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:34 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/31 12:10:18 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_philo *philo)
{
	bool	res;

	if (mutex_lock(&philo->mtxes[TIME],
			&philo->mtxes[ERR], philo->err) == FAIL)
		return (true);
	res = get_timestamp() - philo->last_meal_time > philo->time_to_die;
	if (mutex_unlock(&philo->mtxes[TIME],
			&philo->mtxes[ERR], philo->err) == FAIL)
		return (true);
	return (res);
}

static bool	is_end_dinner(t_philo *philo)
{
	bool	res;

	if (mutex_lock(&philo->mtxes[COUNT],
			&philo->mtxes[ERR], philo->err) == FAIL)
		return (true);
	res = philo->should_count_eat
		&& *(philo->full_num) >= philo->num;
	if (mutex_unlock(&philo->mtxes[COUNT],
			&philo->mtxes[ERR], philo->err) == FAIL)
		return (true);
	return (res);
}

// static bool	is_err_occured_while_dinner(t_philo *philo)
// {
// 	bool	res;

// 	if (pthread_mutex_lock(&philo->mtxes[ERR]) != 0)
// 		return (true);
// 	res = is_err_occured(philo->err);
// 	if (pthread_mutex_unlock(&philo->mtxes[ERR]) != 0)
// 		return (true);
// 	return (res);
// }

static void	kill_philos(t_philo *philo)
{
	set_end_flag(philo);
}

void	*monitor(void *argp)
{
	t_philo	*philos;
	size_t	i;

	philos = (t_philo *)argp;
	i = 1;
	while (true)
	{
		if (i >= philos[1].num)
			i = 1;
		if (is_dead(&philos[i]))
		{
			print_action(&philos[i], "died");
			break ;
		}
		// if (is_err_occured_while_dinner(&philos[i])
			// || is_end_dinner(&philos[i]))
		if (is_end_dinner(&philos[i]))
			break ;
		i++;
	}
	kill_philos(&philos[i]);
	return (NULL);
}
