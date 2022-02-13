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
