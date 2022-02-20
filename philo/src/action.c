#include "philo.h"

void	philo_think(t_philo_info *philo)
{
	if (is_end_simulation(philo))
		return ;
	if (!is_end_simulation(philo))
	{
		print_action(philo, philo->mtx_for_print, philo->index, "is thinking");
	}
}

void	philo_eat(t_philo_info *philo)
{
	if (is_end_simulation(philo))
		return ;
	while (!is_end_simulation(philo))
	{
		get_forks(philo);
		if (philo->own_state == READY_TO_EAT)
			break ;
		if (philo->own_state == HOLD_FORK_IN_RIGHT)
			put_fork_on_rightside(philo);
		if (philo->own_state == HOLD_FORK_IN_LEFT)
			put_fork_on_leftside(philo);
		// usleep(100);
	}
	if (!is_end_simulation(philo))
	{
		print_action(philo, philo->mtx_for_print, philo->index, "is eating");
		my_msleep(philo->time_to_eat, philo);
		philo->last_meal_time = get_timestamp(philo);
	}
}

void	philo_sleep(t_philo_info *philo)
{
	if (is_end_simulation(philo))
		return ;
	if (!is_end_simulation(philo))
	{
		put_forks(philo);
		print_action(philo, philo->mtx_for_print, philo->index, "is sleeping");
		my_msleep(philo->time_to_sleep, philo);
	}
}

bool	is_ready_to_start_simulation(t_philo_info *philo)
{
	bool	res;

	pthread_mutex_lock(philo->mtx_for_status);
	res = (philo->sim_state->kind == READY_TO_START);
	pthread_mutex_unlock(philo->mtx_for_status);
	return (res);
}

void	wait_for_other_threads(t_philo_info *philo)
{
	while (true)
	{
		// if (philo->sim_state->kind == READY_TO_START)
		if (is_ready_to_start_simulation(philo))
			return ;
		my_usleep(100, philo);
	}
}

void	*do_action(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	wait_for_other_threads(philo);
	if (philo->index % 2 == 0)
	{
		my_msleep(2, philo);
	}
	philo->last_meal_time = get_timestamp(philo);
	while (!is_end_simulation(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_exit(NULL);
}
