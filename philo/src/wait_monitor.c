#include "philo.h"

int	wait_monitor(t_philo **philo, t_error_kind *err)
{
	if (pthread_join((*philo)[1].monitor_id, NULL) != 0)
	{
		set_err(err, JOIN_THREAD);
		return (1);
	}
	return (0);
}

int	wait_philo(t_philo **philo, t_error_kind *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_join((*philo)[i].philo_id, NULL) != 0)
		{
			set_err(err, JOIN_THREAD);
			return (1);
		}
		i++;
	}
	return (0);
}

int	destroy_mutex(t_philo **philo, t_error_kind *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_mutex_destroy(&(*philo)[1].forks[i]) != 0)
		{
			set_err(err,DESTROY_MTX);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_destroy((*philo)[1].log) != 0
		|| pthread_mutex_destroy((*philo)[1].state) != 0
		|| pthread_mutex_destroy((*philo)[1].count) != 0
		|| pthread_mutex_destroy((*philo)[1].time) != 0
		|| pthread_mutex_destroy((*philo)[1].mtx_err) != 0)
	{
		set_err(err,DESTROY_MTX);
		return (1);
	}
	return (0);
}
