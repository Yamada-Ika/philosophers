#include "philo.h"

static int	get_fork_on_leftside(t_philo *philo)
{
	int	leftside_index;

	leftside_index = get_index(philo->index + 1, philo->philo_number);
	if (mutex_lock(&philo->forks[leftside_index], philo->mtx_err, philo->err) != 0
		|| print_action(philo, "has taken a fork") != 0)
	{
		return (1);
	}
	return (0);
	// print_action(philo, "has taken a fork");
}

static int	get_fork_on_rightside(t_philo *philo)
{
	if (mutex_lock(&philo->forks[philo->index], philo->mtx_err, philo->err) != 0
		|| print_action(philo, "has taken a fork") != 0)
	{
		return (1);
	}
	return (0);
	// print_action(philo, "has taken a fork");
}

static void	wait_a_moment(void)
{
	usleep(100);
}

static int	get_forks_even_group(t_philo *philo)
{
	wait_a_moment();
	if (get_fork_on_leftside(philo) != 0
		|| get_fork_on_rightside(philo) != 0)
	{
		return (1);
	}
	return (0);
}

static int	get_forks_odd_group(t_philo *philo)
{
	wait_a_moment();
	if (get_fork_on_rightside(philo) != 0
		|| get_fork_on_leftside(philo) != 0)
	{
		return (1);
	}
	return (0);
}

int	get_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		// usleep(100);
		// get_fork_on_leftside(philo);
		// get_fork_on_rightside(philo);
		return (get_forks_even_group(philo));
	}
	else
	{
		// usleep(100);
		// get_fork_on_rightside(philo);
		// get_fork_on_leftside(philo);
		return (get_forks_odd_group(philo));
	}
}
