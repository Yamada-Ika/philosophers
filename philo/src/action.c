#include "philo.h"

void	philo_think(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	if (!is_somephilo_dead(philo))
	{
		print_action(philo->mtx_for_print, philo->index, "is thinking");
	}
}

void	philo_eat(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	while (!is_somephilo_dead(philo))
	{
		get_forks(philo);
		if (philo->own_status_kind == READY_TO_EAT)
			break ;
		if (philo->own_status_kind == HOLD_FORK_IN_LEFT)
			put_fork_on_rightside(philo);
		if (philo->own_status_kind == HOLD_FORK_IN_RIGHT)
			put_fork_on_leftside(philo);
	}
	if (!is_somephilo_dead(philo))
	{
		print_action(philo->mtx_for_print, philo->index, "is eating");
		my_msleep(philo->time_to_eat, philo);
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
		print_action(philo->mtx_for_print, philo->index, "is sleeping");
		my_msleep(philo->time_to_sleep, philo);
	}
}

void	wait_for_other_threads(t_philo_info *philo)
{
	while (true)
	{
		if (philo->shared_status->kind == READY_TO_START)
			return ;
		my_usleep(1000, philo);
	}
}

void	*do_action(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	wait_for_other_threads(philo);
	if (philo->is_even_group)
	{
		my_msleep(2, philo);
	}
	philo->last_meal_time = get_timestamp();
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
	// pthread_exit(NULL);
}
