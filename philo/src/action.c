#include "philo.h"

void	philo_think(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	if (!is_somephilo_dead(philo))
	{
		pthread_mutex_lock(philo->mutex);
		printf("%lld %d is thinking\n", get_timestamp(), philo->index);
		pthread_mutex_unlock(philo->mutex);
	}
}

void	philo_eat(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	while (!is_somephilo_dead(philo))
	{
		get_forks(philo);
		if (philo->has_fork_on_lefthand && philo->has_fork_on_righthand)
			break ;
		if (philo->has_fork_on_lefthand && !philo->has_fork_on_lefthand)
			put_fork_on_rightside(philo);
		if (!philo->has_fork_on_lefthand && philo->has_fork_on_lefthand)
			put_fork_on_leftside(philo);
	}
	if (!is_somephilo_dead(philo))
	{
		pthread_mutex_lock(philo->mutex);
		printf("%lld %d is eating\n", get_timestamp(), philo->index);
		pthread_mutex_unlock(philo->mutex);
		my_usleep(philo->time_to_eat * 1000, philo);
		philo->last_meal_time = get_timestamp();
	}
}

void	philo_sleep(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	if (!is_somephilo_dead(philo))
	{
		put_forks(philo);
		pthread_mutex_lock(philo->mutex);
		printf("%lld %d is sleeping\n", get_timestamp(), philo->index);
		pthread_mutex_unlock(philo->mutex);
		my_usleep(philo->time_to_sleep * 1000, philo);
	}
}

void	wait_for_other_philo(t_philo_info *philo)
{
	while (true)
	{
		if (philo->status->can_start)
			break ;
	}
	philo->last_meal_time = get_timestamp();
	if (philo->is_even_group)
		my_usleep(1000, philo);
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
		philo_eat(philo);
		if (is_somephilo_dead(philo))
			pthread_exit(NULL);
		philo_sleep(philo);
		if (is_somephilo_dead(philo))
			pthread_exit(NULL);
		philo_think(philo);
	}
	pthread_exit(NULL);
}
