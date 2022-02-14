#include "philo.h"

bool	is_over_time_to_die(t_philo_info *philo)
{
	bool	res;

	pthread_mutex_lock(&philo->mutex);
	res = (get_timestamp() - philo->last_meal_time > philo->time_to_die);
	pthread_mutex_unlock(&philo->mutex);
	return (res);
}

void	*monitor(void *argp)
{
	t_philo_info	*philo;
	int	i;

	philo = (t_philo_info *)argp;
	i = 1;
	while (true)
	{
		if (i == philo[1].philo_number)
			i = 1;
		if (is_over_time_to_die(&(philo[i])))
		{
			break ;
		}
		i++;
	}
	// if (!philo->status->is_someone_dead)
	// if (!is_somephilo_dead(philo))
	// {
		pthread_mutex_lock(&(philo[i].mutex));
		printf("%lld %d died\n", get_timestamp(), philo[i].index);
		// printf("%lld %d died\n", get_timestamp(), i);
		// philo->status->is_someone_dead = true;
		philo[i].status->is_someone_dead = true;
		pthread_mutex_unlock(&(philo[i].mutex));
	// }
	pthread_exit((void *)true);
}
