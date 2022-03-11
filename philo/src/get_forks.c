#include "philo.h"

void	get_fork_on_leftside(t_philo *philo)
{
	int	leftside_index;

	leftside_index = get_index(philo->index + 1, philo->philo_number);
	mutex_lock(&philo->forks[leftside_index], philo->mtx_err, philo->err);
	print_action(philo, "has taken a fork");
}

void	get_fork_on_rightside(t_philo *philo)
{
	mutex_lock(&philo->forks[philo->index], philo->mtx_err, philo->err);
	print_action(philo, "has taken a fork");
}

void	get_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		usleep(100);
		get_fork_on_leftside(philo);
		get_fork_on_rightside(philo);
	}
	else
	{
		usleep(100);
		get_fork_on_rightside(philo);
		get_fork_on_leftside(philo);
	}
}
