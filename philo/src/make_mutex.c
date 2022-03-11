#include "philo.h"

int	make_mutex(t_philo **philo, t_error_kind *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_mutex_init(&((*philo)[1].forks[i]), NULL) != 0)
		{
			set_err(err, INIT_MTX);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(((*philo)[1].log), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].state), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].count), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].time), NULL) != 0)
	{
		set_err(err, INIT_MTX);
		return (1);
	}
	return (0);
}
