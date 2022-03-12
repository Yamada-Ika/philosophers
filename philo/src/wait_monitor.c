#include "philo.h"

int	wait_monitor(t_philo **philo, t_error_kind *error_num)
{
	if (pthread_join((*philo)[1].monitor_id, NULL) != 0)
	{
		*error_num = JOIN_THREAD;
		return (1);
	}
	return (0);
}

int	wait_philo(t_philo **philo, t_error_kind *error_num)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_join((*philo)[i].philo_id, NULL) != 0)
		{
			*error_num = JOIN_THREAD;
			return (1);
		}
		i++;
	}
	return (0);
}
