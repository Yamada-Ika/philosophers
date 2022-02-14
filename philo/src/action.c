#include "philo.h"

void	philo_think(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %d is thinking\n", get_timestamp(), philo->index);
	pthread_mutex_unlock(&philo->mutex);
	get_forks(philo);
}

void	philo_eat(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %d is eating\n", get_timestamp(), philo->index);
	pthread_mutex_unlock(&philo->mutex);
	my_msleep(philo->time_to_eat);
	philo->last_meal_time = get_timestamp();
}

void	philo_sleep(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	put_forks(philo);
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %d is sleeping\n", get_timestamp(), philo->index);
	pthread_mutex_unlock(&philo->mutex);
	my_msleep(philo->time_to_sleep);
}

void	wait_for_other_philo(t_philo_info *philo)
{
	while (true)
	{
		if (philo->status->can_start)
			break ;
	}
	if (philo->is_even_group)
		my_usleep(100);
}

void	*do_action(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	wait_for_other_philo(philo);
	while (true)
	{
		if (is_somephilo_dead(philo))
			pthread_exit(NULL);
		philo_think(philo);
		if (is_somephilo_dead(philo))
			pthread_exit(NULL);
		philo_eat(philo);
		if (is_somephilo_dead(philo))
			pthread_exit(NULL);
		philo_sleep(philo);
		my_usleep(100);
	}
	pthread_exit(NULL);
}
