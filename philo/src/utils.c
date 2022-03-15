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
	if (mutex_lock(philo->state, philo->mtx_err, philo->err) != 0)
		return (1);
	if (*(philo->is_end))
	{
		if (mutex_unlock(philo->state, philo->mtx_err, philo->err) != 0)
			return (1);
		return (1);
	}
	if (mutex_unlock(philo->state, philo->mtx_err, philo->err) != 0)
		return (1);
	if (mutex_lock(philo->log, philo->mtx_err, philo->err) != 0)
		return (1);
	printf("%lld %zu", get_timestamp(), philo->index);
	printf(" %s\n", action);
	if (mutex_unlock(philo->log, philo->mtx_err, philo->err) != 0)
		return (1);
	return (0);
}
