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

// long long	get_timestamp_in_usec(void)
// {
// 	t_time		tv;
// 	long long	timestamp;

// 	if (gettimeofday(&tv, NULL) == 0)
// 	{
// 		timestamp = tv.tv_sec * 1000000 + tv.tv_usec;
// 		return (timestamp);
// 	}
// 	return (0);
// }

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

// void	my_usleep(long long usec)
// {
// 	long long	start;

// 	start = get_timestamp_in_usec();
// 	while (true)
// 	{
// 		if (get_timestamp_in_usec() - start >= usec)
// 			return ;
// 		usleep(1);
// 	}
// }
