#include "philo.h"

static void	update_mealtime(t_philo *philo)
{
	mutex_lock(philo->time, philo->mtx_err, philo->err);
	philo->last_meal_time = get_timestamp();
	mutex_unlock(philo->time, philo->mtx_err, philo->err);
}

int	philo_think(t_philo *philo)
{
	return (print_action(philo, "is thinking"));
}

int	philo_eat(t_philo *philo)
{
	get_forks(philo);
	if (print_action(philo, "is eating") != 0)
		return (1);
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
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	put_forks(philo);
	// print_action(philo, "is sleeping");
	if (print_action(philo, "is sleeping") != 0)
		return (1);
	my_msleep(philo->time_to_sleep);
	return (0);
}

void	*do_action(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	update_mealtime(philo);
	while (true)
	{
		// philo_eat(philo);
		// philo_sleep(philo);
		// philo_think(philo);
		if (philo_eat(philo) != 0
			|| philo_sleep(philo) != 0
			|| philo_think(philo) != 0)
		{
			pthread_exit(NULL);
		}
	}
	pthread_exit(NULL);
}
