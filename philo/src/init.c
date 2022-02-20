#include "philo.h"

t_philo_info	*init_philo(t_arg_info *argt)
{
	t_philo_info	*philo;
	bool	*forks;
	t_sim_state	*status;
	pthread_mutex_t	*mtx_for_print;
	pthread_mutex_t	*mtx_for_fork;
	pthread_mutex_t	*mtx_for_status;
	int	i;

	philo = (t_philo_info *)calloc(argt->number_of_philosophers + 1, sizeof(t_philo_info));
	forks = (bool *)calloc(argt->number_of_philosophers + 1, sizeof(bool));
	status = (t_sim_state *)calloc(1, sizeof(t_sim_state));
	status->kind = WAIT_OTHERS;
	mtx_for_print = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
	mtx_for_fork = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
	mtx_for_status = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
	i = 1;
	while (i < argt->number_of_philosophers + 1)
	{
		forks[i] = true;
		philo[i].index = i;
		philo[i].sim_state = status;
		philo[i].own_state = HOLD_NOTHING;
		philo[i].forks = forks;
		philo[i].philo_number = argt->number_of_philosophers;
		philo[i].time_to_eat = argt->time_to_eat;
		philo[i].time_to_sleep = argt->time_to_sleep;
		philo[i].time_to_die = argt->time_to_die;
		philo[i].last_meal_time = get_timestamp();
		philo[i].mtx_for_print = mtx_for_print;
		philo[i].mtx_for_fork = mtx_for_fork;
		philo[i].mtx_for_status = mtx_for_status;
		i++;
	}
	return (philo);
}

bool	can_init_mutex(t_philo_info *philo)
{
	// int	i;

	// i = 1;
	// while (i < philo[1].philo_number + 1)
	// {
	if (pthread_mutex_init(philo[1].mtx_for_print, NULL) != 0)
	{
		return (false);
	}
	if (pthread_mutex_init(philo[1].mtx_for_fork, NULL) != 0)
	{
		return (false);
	}
	if (pthread_mutex_init(philo[1].mtx_for_status, NULL) != 0)
	{
		return (false);
	}
	// }
	return (true);
}

bool	can_destroy_mutex(t_philo_info *philo)
{
	if (pthread_mutex_destroy(philo[1].mtx_for_print) != 0)
	{
		return (false);
	}
	if (pthread_mutex_destroy(philo[1].mtx_for_fork) != 0)
	{
		return (false);
	}
	if (pthread_mutex_destroy(philo[1].mtx_for_status) != 0)
	{
		return (false);
	}
	return (true);
}

bool	can_create_thread(t_philo_info *philo)
{
	int	i;

	i = 1;
	while (i < philo[1].philo_number + 1)
	{
		if (pthread_create(&(philo[i].philo_id), NULL, do_action, &(philo[i])) != 0)
		{
			return (false);
		}
		if (pthread_create(&(philo[i].monitor_id), NULL, monitor, &(philo[i])) != 0)
		{
			return (false);
		}
		i++;
	}
	philo[1].sim_state->kind = READY_TO_START;
	return (true);
}

bool	can_join_thread(t_philo_info *philo)
{
	int	i;

	i = 1;
	while (i < philo[1].philo_number + 1)
	{
		if (pthread_join(philo[i].philo_id, NULL) != 0)
		{
			return (false);
		}
		if (pthread_join(philo[i].monitor_id, NULL) != 0)
		{
			return (false);
		}
		i++;
	}
	return (true);
}
