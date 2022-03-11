#include "philo.h"

void	put_fork_on_leftside(t_philo *philo)
{
	int	leftside_index;

	leftside_index = get_index(philo->index + 1, philo->philo_number);
	pthread_mutex_unlock(&(philo->forks[leftside_index]));
}

void	put_fork_on_rightside(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->forks[philo->index]));
}

void	put_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		put_fork_on_leftside(philo);
		put_fork_on_rightside(philo);
	}
	else
	{
		put_fork_on_rightside(philo);
		put_fork_on_leftside(philo);
	}
}
