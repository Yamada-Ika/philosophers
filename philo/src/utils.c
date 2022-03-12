#include "philo.h"

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
	mutex_lock(philo->state, philo->mtx_err, philo->err);
	if (*(philo->is_end))
	{
		mutex_unlock(philo->state, philo->mtx_err, philo->err);
		return (1);
	}
	mutex_unlock(philo->state, philo->mtx_err, philo->err);
	mutex_lock(philo->log, philo->mtx_err, philo->err);
	printf("%lld %zu", get_timestamp(), philo->index);
	printf(" %s\n", action);
	mutex_unlock(philo->log, philo->mtx_err, philo->err);
	return (0);
}
