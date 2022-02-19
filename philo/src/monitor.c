#include "philo.h"

// bool	is_over_time_to_die(t_philo_info *philo)
// {
// 	bool	res;

// 	pthread_mutex_lock(philo->mtx_for_print);
// 	res = (get_timestamp() - philo->last_meal_time > philo->time_to_die);
// 	pthread_mutex_unlock(philo->mtx_for_print);
// 	return (res);
// }

void	*monitor(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	wait_for_other_threads(philo);
	pthread_exit(NULL);
	while (true)
	{
		if (get_timestamp() - philo->last_meal_time > philo->time_to_die)
		{
			break ;
		}
		// my_usleep(100, philo);
	}
	if (!is_somephilo_dead(philo))
	{
		// pthread_mutex_lock(philo->mtx_for_print);
		philo->sim_state->kind = SOMEONE_DEAD;
		print_action(philo->mtx_for_print, philo->index, "died");
		// printf("%lld %d died\n", get_timestamp(), philo->index);
		// pthread_mutex_unlock(philo->mtx_for_print);
	}
	// pthread_exit(NULL);
}
