#include "philo.h"

int	lock_philo_threads(t_philo *philo)
{
	return (pthread_mutex_lock(philo->log));
}

// void	kill_other_monitors(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->state);
// 	*(philo->is_end) = true;
// 	pthread_mutex_unlock(philo->state);
// }

// bool	is_sim_end(t_philo *philo)
// {
// 	bool	res;

// 	pthread_mutex_lock(philo->state);
// 	res = *(philo->is_end);
// 	pthread_mutex_unlock(philo->state);
// 	return (res);
// }

// bool	is_all_philos_eat(t_philo *philo)
// {
// 	bool	res;

// 	pthread_mutex_lock(philo->count);
// 	res = *(philo->full_num) >= philo->philo_number;
// 	pthread_mutex_unlock(philo->count);
// 	return (res);
// }

bool	is_dead(t_philo *philo)
{
	bool	res;

	pthread_mutex_lock(philo->time);
	res = get_timestamp() - philo->last_meal_time > philo->time_to_die;
	pthread_mutex_unlock(philo->time);
	return (res);
}

bool	is_end_dinner(t_philo *philo)
{
	return (philo->should_count_eat
		&& *(philo->full_num) >= philo->philo_number);
}

void	*monitor(void *argp)
{
	t_philo	*philo;
	int		i;
	int		philo_num;

	philo = (t_philo *)argp;
	philo_num = philo[1].philo_number;
	i = 1;
	while (true)
	{
		if (i >= philo_num)
			i = 1;
		if (is_dead(&philo[i]))
			break ;
		if (is_end_dinner(&(philo[i])))
		{
			pthread_mutex_lock(philo[i].log);
			pthread_exit(NULL);
		}
		i++;
	}
	print_action(philo[i].log, philo[i].index, "died");
	pthread_mutex_lock(philo[i].log);
	pthread_exit(NULL);
}
