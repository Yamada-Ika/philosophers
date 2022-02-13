#include "philo.h"

void	*monitor(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	while (true)
	{
		// long long cur_time = get_timestamp();
		if (get_timestamp() - philo->last_meal_time > philo->time_to_die)
		{
			// printf("dead time: %lld\n", cur_time);
			break ;
		}
	}
	if (!philo->status->is_someone_dead)
		printf("%lld %d died\n", get_timestamp(), philo->index);
	philo->status->is_someone_dead = true;
	pthread_exit((void *)true);
}
