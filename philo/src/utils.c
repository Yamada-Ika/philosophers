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

int	print_action(t_philo *philo, char *action)
{
	mutex_lock(philo->log, philo->mtx_err, philo->err);
	printf("%lld %zu", get_timestamp(), philo->index);
	printf(" %s\n", action);
	mutex_unlock(philo->log, philo->mtx_err, philo->err);
	return (0);
}
