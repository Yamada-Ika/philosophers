#include "philo.h"

int	get_index(int index, int philos_number)
{
	if (index == 0)
		return (philos_number);
	else if (index == philos_number + 1)
		return (1);
	else
		return (index);
}

long long	get_timestamp(void)
{
	t_time	tv;

	if (gettimeofday(&tv, NULL) == 0)
	{
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	}
	return (0);
}

bool	is_somephilo_dead(t_philo_info *philo)
{
	bool	res;

	pthread_mutex_lock(&philo->mutex);
	res = philo->status->is_someone_dead;
	pthread_mutex_unlock(&philo->mutex);
	return (res);
}

void	my_msleep(long long msec)
{
	long long	start;

	start = get_timestamp();
	while (true)
	{
		if (get_timestamp() - start >= msec)
			return ;
	}
}

long long	get_timestamp_in_usec(void)
{
	t_time	tv;

	if (gettimeofday(&tv, NULL) == 0)
	{
		// printf("sec  : %zu\n", tv.tv_sec * 1000000);
		// printf("usec : %d\n", tv.tv_usec);
		return (tv.tv_sec * 1000000 + tv.tv_usec);
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
	}
}
