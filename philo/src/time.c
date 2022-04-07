/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:17:12 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/07 10:17:19 by iyamada          ###   ########.fr       */
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

static long long	get_timestamp_in_usec(void)
{
	t_time		tv;
	long long	time;

	if (gettimeofday(&tv, NULL) == 0)
	{
		time = tv.tv_sec * 1000000 + tv.tv_usec;
		return (time);
	}
	return (0);
}

void	my_usleep(long long usec)
{
	long long	start;

	start = get_timestamp_in_usec();
	while (true)
	{
		if (get_timestamp_in_usec() - start >= usec)
			return ;
		usleep(10);
	}
}

int	my_msleep(t_philo *philo, long long msec)
{
	long long	start;

	start = get_timestamp();
	while (true)
	{
		if (get_timestamp() - start >= msec)
			return (SUCCESS);
		if (is_someone_dead(philo))
			return (FAIL);
		usleep(100);
	}
}
