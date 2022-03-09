#include "philo.h"

int	lock_philo_threads(t_philo *philo)
{
	return (pthread_mutex_lock(philo->log));
}

void	kill_other_monitors(t_philo *philo)
{
	pthread_mutex_lock(philo->state);
	*(philo->is_end) = true;
	pthread_mutex_unlock(philo->state);
}

bool	is_sim_end(t_philo *philo)
{
	bool	res;

	pthread_mutex_lock(philo->state);
	res = *(philo->is_end);
	pthread_mutex_unlock(philo->state);
	return (res);
}

bool	is_all_philos_eat(t_philo *philo)
{
	bool	res;

	pthread_mutex_lock(philo->count);
	res = *(philo->full_num) >= philo->philo_number;
	pthread_mutex_unlock(philo->count);
	return (res);
}

bool	is_hungry(t_philo *philo)
{
	bool	res;

	pthread_mutex_lock(philo->time);
	res = get_timestamp() - philo->last_meal_time > philo->time_to_die;
	pthread_mutex_unlock(philo->time);
	return (res);
}

void	*monitor(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	wait_all_thread(philo);
	while (true)
	{
		if (is_sim_end(philo))
		{
			pthread_exit((void *)1);
		}
		if (is_hungry(philo))
		{
			break ;
		}
		pthread_mutex_lock(philo->count);
		if (!is_sim_end(philo) && philo->must_eat_times != -1 && *(philo->full_num) >= philo->philo_number)
		{
			lock_philo_threads(philo);
			kill_other_monitors(philo);
			pthread_mutex_unlock(philo->count);
			pthread_exit((void *)1);
		}
		pthread_mutex_unlock(philo->count);
	}
	print_action(philo->log, philo->index, "died");
	lock_philo_threads(philo);
	kill_other_monitors(philo);
	pthread_exit(NULL);
}
