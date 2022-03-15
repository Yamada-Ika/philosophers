/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:30:03 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/16 00:48:12 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	t_time		tv;
	long long	time;

	if (gettimeofday(&tv, NULL) == 0)
	{
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		return (time);
	}
	return (0);
}

void	my_msleep(long long msec)
{
	long long	start;

	start = get_timestamp();
	while (true)
	{
		if (get_timestamp() - start >= msec)
			return ;
		usleep(500);
	}
}

int	get_index(int index, int philo_num)
{
	if (index == 0)
		return (philo_num);
	else if (index == philo_num + 1)
		return (1);
	else
		return (index);
}

int	print_action(t_philo *philo, char *action)
{
	if (mutex_lock(philo->state, philo->mtx_err, philo->err) != 0)
		return (1);
	if (*(philo->is_end))
	{
		if (mutex_unlock(philo->state, philo->mtx_err, philo->err) != 0)
			return (1);
		return (1);
	}
	if (mutex_unlock(philo->state, philo->mtx_err, philo->err) != 0)
		return (1);
	if (mutex_lock(philo->log, philo->mtx_err, philo->err) != 0)
		return (1);
	printf("%lld %zu", get_timestamp(), philo->index);
	printf(" %s\n", action);
	if (mutex_unlock(philo->log, philo->mtx_err, philo->err) != 0)
		return (1);
	return (0);
}
