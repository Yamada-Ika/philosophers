#include "philo.h"

void	philo_think(t_philo_info *philo)
{
	if (philo->status->is_someone_dead)
		return ;
	printf("%lld %d is thinking\n", get_timestamp(), philo->index);
	get_forks(philo);
}

void	philo_eat(t_philo_info *philo)
{
	if (philo->status->is_someone_dead)
		return ;
	printf("%lld %d is eating\n", get_timestamp(), philo->index);
	usleep(philo->time_to_eat * 1000);
	philo->last_meal_time = get_timestamp();
}

void	philo_sleep(t_philo_info *philo)
{
	if (philo->status->is_someone_dead)
		return ;
	put_forks(philo);
	printf("%lld %d is sleeping\n", get_timestamp(), philo->index);
	usleep(philo->time_to_sleep * 1000);
}

void	*do_action(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	while (true)
	{
		if (philo->status->is_someone_dead)
			pthread_exit(NULL);
		philo_think(philo);
		if (philo->status->is_someone_dead)
			pthread_exit(NULL);
		philo_eat(philo);
		if (philo->status->is_someone_dead)
			pthread_exit(NULL);
		philo_sleep(philo);
	}
	pthread_exit(NULL);
	// pthread_mutex_lock(&philo->mutex);
	// pthread_mutex_unlock(&philo->mutex);
}
