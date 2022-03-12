#include "philo.h"

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

void	set_end_dinner_flag(t_philo *philo)
{
	mutex_lock(philo->state, philo->mtx_err, philo->err);
	*(philo->is_end) = true;
	mutex_unlock(philo->state, philo->mtx_err, philo->err);
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
			set_end_dinner_flag(&philo[i]);
			return (NULL);
		}
		i++;
	}
	print_action(&philo[i], "died");
	set_end_dinner_flag(&philo[i]);
	return (NULL);
}
