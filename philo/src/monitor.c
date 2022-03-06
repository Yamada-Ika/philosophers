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

void	wait_philos(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(philo->state);
		if (*(philo->is_init))
		{
			pthread_mutex_unlock(philo->state);
			break ;
		}
		pthread_mutex_unlock(philo->state);
		usleep(1);
	}
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

void	*monitor(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	wait_odd_group(philo);
	while (true)
	{
		if (is_sim_end(philo))
		{
			pthread_exit((void *)1);
		}
		if (!is_sim_end(philo) && get_timestamp() - philo->last_meal_time > philo->time_to_die)
		{
			break ;
		}
		if (!is_sim_end(philo) && philo->must_eat_times != -1 && is_all_philos_eat(philo))
		{
			kill_other_monitors(philo);
			lock_philo_threads(philo);
			pthread_exit((void *)1);
		}
	}
	kill_other_monitors(philo);
	print_action(philo->log, philo->index, "died");
	lock_philo_threads(philo);
	pthread_exit((void *)1);
}
