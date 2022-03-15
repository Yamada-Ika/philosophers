#include "philo.h"

static int	put_fork_on_leftside(t_philo *philo)
{
	int	leftside_index;

	leftside_index = get_index(philo->index + 1, philo->philo_number);
	return (mutex_unlock(&(philo->forks[leftside_index]), philo->mtx_err, philo->err));
}

static int	put_fork_on_rightside(t_philo *philo)
{
	return (mutex_unlock(&(philo->forks[philo->index]), philo->mtx_err, philo->err));
}

static int	put_forks_even_group(t_philo *philo)
{
	if (put_fork_on_leftside(philo) != 0
		|| put_fork_on_rightside(philo) != 0)
	{
		return (1);
	}
	return (0);
}

static int	put_forks_odd_group(t_philo *philo)
{
	if (put_fork_on_rightside(philo) != 0
		|| put_fork_on_leftside(philo) != 0)
	{
		return (1);
	}
	return (0);
}

int	put_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		// put_fork_on_leftside(philo);
		// put_fork_on_rightside(philo);
		return (put_forks_even_group(philo));
	}
	else
	{
		// put_fork_on_rightside(philo);
		// put_fork_on_leftside(philo);
		return (put_forks_odd_group(philo));
	}
}
