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

void	print_action(t_mutex *mtx, int index, char *action)
{
	pthread_mutex_lock(mtx);
	printf("%lld %d", get_timestamp(), index);
	printf(" %s\n", action);
	pthread_mutex_unlock(mtx);
}
