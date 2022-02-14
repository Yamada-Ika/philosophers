#include "philo.h"

void	philo_think(t_philo_info *philo)
{
	// if (philo->status->is_someone_dead)
	if (is_somephilo_dead(philo))
		return ;
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %d is thinking\n", get_timestamp(), philo->index);
	pthread_mutex_unlock(&philo->mutex);
	get_forks(philo);
}

void	philo_eat(t_philo_info *philo)
{
	// if (philo->status->is_someone_dead)
	if (is_somephilo_dead(philo))
		return ;
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %d is eating\n", get_timestamp(), philo->index);
	pthread_mutex_unlock(&philo->mutex);
	usleep(philo->time_to_eat * 1000);
	philo->last_meal_time = get_timestamp();
}

void	philo_sleep(t_philo_info *philo)
{
	// if (philo->status->is_someone_dead)
	if (is_somephilo_dead(philo))
		return ;
	put_forks(philo);
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %d is sleeping\n", get_timestamp(), philo->index);
	pthread_mutex_unlock(&philo->mutex);
	usleep(philo->time_to_sleep * 1000);
}

void	*do_action(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	while (true)
	{
		// if (philo->status->is_someone_dead)
		if (is_somephilo_dead(philo))
			pthread_exit(NULL);
		philo_think(philo);
		// if (philo->status->is_someone_dead)
		if (is_somephilo_dead(philo))
			pthread_exit(NULL);
		philo_eat(philo);
		// if (philo->status->is_someone_dead)
		if (is_somephilo_dead(philo))
			pthread_exit(NULL);
		philo_sleep(philo);
		usleep(100);
	}
	pthread_exit(NULL);
	// pthread_mutex_lock(&philo->mutex);
	// pthread_mutex_unlock(&philo->mutex);
}
