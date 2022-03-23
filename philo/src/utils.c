/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:30:03 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 21:38:21 by iyamada          ###   ########.fr       */
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

static int	is_someone_dead(t_philo *philo, bool *res)
{
	if (mutex_lock(&philo->mtxs[STATE], &philo->mtxs[ERR], philo->err) != 0)
		return (-1);
	if (*(philo->is_end))
	{
		if (mutex_unlock(&philo->mtxs[STATE], &philo->mtxs[ERR], philo->err) != 0)
			return (-1);
		*res = true;
		return (0);
	}
	if (mutex_unlock(&philo->mtxs[STATE], &philo->mtxs[ERR], philo->err) != 0)
		return (-1);
	*res = false;
	return (0);
}

int	my_msleep(t_philo *philo, long long msec)
{
	long long	start;
	bool		should_end;

	should_end = false;
	start = get_timestamp();
	while (true)
	{
		if (is_someone_dead(philo, &should_end) != 0)
			return (1);
		if (get_timestamp() - start >= msec || should_end)
			return (0);
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
	bool	should_end;

	if (is_someone_dead(philo, &should_end) != 0)
		return (1);
	if (should_end)
		return (1);
	if (mutex_lock(&philo->mtxs[LOG], &philo->mtxs[ERR], philo->err) != 0)
		return (1);
	printf("%lld %zu", get_timestamp(), philo->index);
	printf(" %s\n", action);
	if (mutex_unlock(&philo->mtxs[LOG], &philo->mtxs[ERR], philo->err) != 0)
		return (1);
	return (0);
}
