#include "philo.h"

// bool	is_over_time_to_die(t_philo_info *philo)
// {
// 	bool	res;

// 	pthread_mutex_lock(philo->mtx_for_print);
// 	res = (get_timestamp(philo) - philo->last_meal_time > philo->time_to_die);
// 	pthread_mutex_unlock(philo->mtx_for_print);
// 	return (res);
// }

void	*monitor(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	wait_for_other_threads(philo);
	while (true)
	{
		if (get_timestamp(philo) - philo->last_meal_time > philo->time_to_die)
		{
			break ;
		}
		// my_usleep(100, philo);
	}
	if (!is_end_simulation(philo))
	{
		pthread_mutex_lock(philo->mtx_for_status);
		philo->sim_state->kind = END_SIMULATION;
		pthread_mutex_unlock(philo->mtx_for_status);
		print_action(philo, philo->mtx_for_print, philo->index, "died");
	}
	pthread_exit(NULL);
}
