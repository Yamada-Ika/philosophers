/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:30:03 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/29 00:11:47 by iyamada          ###   ########.fr       */
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
		usleep(1);
	}
}

static int	is_someone_dead(t_philo *p, bool *res)
{
	if (mutex_lock(&p->mtxes[STATE], &p->mtxes[ERR], p->err) != 0)
		return (FAIL);
	if (*(p->should_end))
	{
		if (mutex_unlock(&p->mtxes[STATE], &p->mtxes[ERR], p->err) != 0)
			return (FAIL);
		*res = true;
		return (SUCCESS);
	}
	if (mutex_unlock(&p->mtxes[STATE], &p->mtxes[ERR], p->err) != 0)
		return (FAIL);
	*res = false;
	return (SUCCESS);
}

int	my_msleep(t_philo *philo, long long msec)
{
	long long	start;
	bool		should_end;

	should_end = false;
	start = get_timestamp();
	while (true)
	{
		if (is_someone_dead(philo, &should_end) == FAIL)
			return (FAIL);
		if (get_timestamp() - start >= msec || should_end)
			return (SUCCESS);
		usleep(100);
	}
}

int	get_index(t_philo *philo, size_t index)
{
	if (index == 0)
		return (philo->num);
	else if (index == philo->num + 1)
		return (1);
	else
		return (index);
}

int	print_action(t_philo *p, char *action)
{
	bool	should_end;

	if (is_someone_dead(p, &should_end) == FAIL
		|| should_end
		|| mutex_lock(&p->mtxes[LOG], &p->mtxes[ERR], p->err) == FAIL)
	{
		return (FAIL);
	}
	printf("%lld %zu %s\n", get_timestamp(), p->index, action);
	return (mutex_unlock(&p->mtxes[LOG], &p->mtxes[ERR], p->err));
}
