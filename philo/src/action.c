#include "philo.h"

static void	update_mealtime(t_philo *philo)
{
	mutex_lock(philo->time, philo->mtx_err, philo->err);
	philo->last_meal_time = get_timestamp();
	mutex_unlock(philo->time, philo->mtx_err, philo->err);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	get_forks(philo);
	print_action(philo, "is eating");
	my_msleep(philo->time_to_eat);
	update_mealtime(philo);
	philo->eat_count++;
	if (!philo->is_full
		&& philo->should_count_eat
		&& philo->eat_count >= philo->must_eat_times)
	{
		philo->is_full = true;
		mutex_lock(philo->count, philo->mtx_err, philo->err);
		*(philo->full_num) += 1;
		mutex_unlock(philo->count, philo->mtx_err, philo->err);
	}
}

void	philo_sleep(t_philo *philo)
{
	put_forks(philo);
	print_action(philo, "is sleeping");
	my_msleep(philo->time_to_sleep);
}

void	*do_action(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	update_mealtime(philo);
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_exit(NULL);
}
