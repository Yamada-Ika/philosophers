#include "philo.h"

void	philo_think(t_philo *philo)
{
	print_action(philo->log, philo->index, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	while (true)
	{
		get_forks(philo);
		if (philo->can_eat)
			break ;
	}
	print_action(philo->log, philo->index, "is eating");
	my_msleep(philo->time_to_eat, philo);
	philo->last_meal_time = get_timestamp();
	philo->eat_count++;
	if (!philo->is_full && philo->must_eat_times != -1 && philo->eat_count >= philo->must_eat_times)
	{
		philo->is_full = true;
		pthread_mutex_lock(philo->count);
		*(philo->full_num) += 1;
		pthread_mutex_unlock(philo->count);
	}
}

void	philo_sleep(t_philo *philo)
{
	put_forks(philo);
	print_action(philo->log, philo->index, "is sleeping");
	my_msleep(philo->time_to_sleep, philo);
}

void	init_mealtime(t_philo *philo)
{
	philo->last_meal_time = get_timestamp();
	// pthread_mutex_lock(philo->state);
	// *(philo->is_init) = true;
	// pthread_mutex_unlock(philo->state);
}

void	*do_action(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	wait_odd_group(philo);
	wait_even_group(philo);
	init_mealtime(philo);
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_exit(NULL);
}
