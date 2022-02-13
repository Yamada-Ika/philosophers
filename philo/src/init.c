#include "philo.h"

t_philo_info	*init_philo(t_arg_info *argt)
{
	t_philo_info	*philo;
	bool	*forks;
	t_philo_status	*status;
	int	i;

	philo = (t_philo_info *)calloc(argt->number_of_philosophers + 1, sizeof(t_philo_info));
	forks = (bool *)calloc(argt->number_of_philosophers + 1, sizeof(bool));
	status = (t_philo_status *)calloc(1, sizeof(t_philo_status));
	status->is_someone_dead = false;
	i = 1;
	while (i < argt->number_of_philosophers + 1)
	{
		forks[i] = true;
		philo[i].index = i;
		philo[i].status = status;
		philo[i].has_fork_on_lefthand = false;
		philo[i].has_fork_on_righthand = false;
		philo[i].forks = forks;
		if (i % 2 == 0)
			philo[i].is_even_group = true;
		else
			philo[i].is_even_group = false;
		philo[i].philo_number = argt->number_of_philosophers;
		philo[i].time_to_eat = argt->time_to_eat;
		philo[i].time_to_sleep = argt->time_to_sleep;
		philo[i].time_to_die = argt->time_to_die;
		philo[i].last_meal_time = get_timestamp();
		i++;
	}
	return (philo);
}

bool	can_init_mutex(t_philo_info *philo)
{
	int	i;

	i = 1;
	while (i < philo[1].philo_number + 1)
	{
		if (pthread_mutex_init(&(philo[i].mutex), NULL) != 0)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	can_destroy_mutex(t_philo_info *philo)
{
	int	i;

	i = 1;
	while (i < philo[1].philo_number + 1)
	{
		if (pthread_mutex_destroy(&(philo[i].mutex)) != 0)
		{
			return (false);
		}
		i++;
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
		if (pthread_create(&(philo[i].philo_id), NULL, monitor, &(philo[i])) != 0)
		{
			return (false);
		}
		i++;
	}
	return (true);
}
