/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:49 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:29:57 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	t_time		tv;
	long long	timestamp;

	if (gettimeofday(&tv, NULL) == 0)
	{
		timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		return (timestamp);
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
