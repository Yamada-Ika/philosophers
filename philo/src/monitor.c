#include "philo.h"

bool	is_over_time_to_die(t_philo_info *philo)
{
	bool	res;

	pthread_mutex_lock(philo->mutex);
	res = (get_timestamp() - philo->last_meal_time > philo->time_to_die);
	pthread_mutex_unlock(philo->mutex);
	return (res);
}

void	*monitor(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	while (true)
	{
		if (is_over_time_to_die(philo))
		{
			break ;
		}
		my_usleep(100, philo);
	}
	if (!is_somephilo_dead(philo))
	{
		pthread_mutex_lock(philo->mutex);
		philo->status->is_someone_dead = true;
		printf("%lld %d died\n", get_timestamp(), philo->index);
		pthread_mutex_unlock(philo->mutex);
	}
	pthread_exit(NULL);
}
