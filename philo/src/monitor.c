#include "philo.h"

int	lock_philo_threads(t_philo *philo)
{
	return (mutex_lock(philo->log, philo->mtx_err, philo->err));
}

bool	is_dead(t_philo *philo)
{
	bool	res;

	mutex_lock(philo->time, philo->mtx_err, philo->err);
	res = get_timestamp() - philo->last_meal_time > philo->time_to_die;
	mutex_unlock(philo->time, philo->mtx_err, philo->err);
	return (res);
}

bool	is_end_dinner(t_philo *philo)
{
	bool	res;

	mutex_lock(philo->count, philo->mtx_err, philo->err);
	res = philo->should_count_eat
		&& *(philo->full_num) >= philo->philo_number;
	mutex_unlock(philo->count, philo->mtx_err, philo->err);
	return (res);
}

bool	is_err_occured_while_dinner(t_philo *philo)
{
	bool	res;

	mutex_lock(philo->mtx_err, philo->mtx_err, philo->err);
	res = is_err_occured(philo->err);
	mutex_unlock(philo->mtx_err, philo->mtx_err, philo->err);
	return (res);
}

void	*monitor(void *argp)
{
	t_philo	*philo;
	size_t	i;
	size_t	philo_num;

	philo = (t_philo *)argp;
	philo_num = philo[1].philo_number;
	i = 1;
	while (true)
	{
		if (i >= philo_num)
			i = 1;
		if (is_dead(&philo[i]))
			break ;
		if (is_err_occured_while_dinner(&philo[i])
			|| is_end_dinner(&philo[i]))
		{
			// mutex_lock(philo[i].log, philo[i].mtx_err, philo[i].err);
			mutex_lock(philo[i].state, philo[i].mtx_err, philo[i].err);
			*(philo[i].is_end) = true;
			mutex_unlock(philo[i].state, philo[i].mtx_err, philo[i].err);
			pthread_exit(NULL);
		}
		i++;
	}
	print_action(&philo[i], "died");
	mutex_lock(philo[i].state, philo[i].mtx_err, philo[i].err);
	*(philo[i].is_end) = true;
	mutex_unlock(philo[i].state, philo[i].mtx_err, philo[i].err);
	// mutex_lock(philo[i].log, philo[i].mtx_err, philo[i].err);
	pthread_exit(NULL);
}
