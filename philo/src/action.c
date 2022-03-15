#include "philo.h"

static int	update_mealtime(t_philo *philo)
{
	if (mutex_lock(philo->time, philo->mtx_err, philo->err) != 0)
		return (1);
	philo->last_meal_time = get_timestamp();
	return (mutex_unlock(philo->time, philo->mtx_err, philo->err));
}

int	philo_think(t_philo *philo)
{
	return (print_action(philo, "is thinking"));
}

int	philo_sleep(t_philo *philo)
{
	// put_forks(philo);
	if (put_forks(philo) != 0
		|| print_action(philo, "is sleeping") != 0)
		return (1);
	my_msleep(philo->time_to_sleep);
	return (0);
}

static int	incre_full_philo(t_philo *philo)
{
	if (mutex_lock(philo->count, philo->mtx_err, philo->err) != 0)
		return (1);
	*(philo->full_num) += 1;
	return (mutex_unlock(philo->count, philo->mtx_err, philo->err));
}

static int	still_hungry(t_philo *philo)
{
	return (!philo->is_full
		&& philo->should_count_eat
		&& philo->eat_count >= philo->must_eat_times);
}

int	philo_eat(t_philo *philo)
{
	if (get_forks(philo) != 0)
		return (1);
	if (print_action(philo, "is eating") != 0)
	{
		put_forks(philo);
		return (1);
	}
	my_msleep(philo->time_to_eat);
	update_mealtime(philo);
	philo->eat_count++;
	if (still_hungry(philo))
	{
		philo->is_full = true;
		return (incre_full_philo(philo));
	}
	return (0);
}

void	*do_action(void *argp)
{
	t_philo	*philo;

	philo = (t_philo *)argp;
	if (update_mealtime(philo) != 0)
		return (NULL);
	while (true)
	{
		if (philo_eat(philo) != 0
			|| philo_sleep(philo) != 0
			|| philo_think(philo) != 0)
		{
			return (NULL);
		}
	}
	return (NULL);
}
