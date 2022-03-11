#include "philo.h"

void	get_fork_on_leftside(t_philo *philo)
{
	int	leftside_index;

	leftside_index = get_index(philo->index + 1, philo->philo_number);
	pthread_mutex_lock(&(philo->forks[leftside_index]));
	print_action(philo->log, philo->index, "has taken a fork");
}

void	get_fork_on_rightside(t_philo *philo)
{
	pthread_mutex_lock(&(philo->forks[philo->index]));
	print_action(philo->log, philo->index, "has taken a fork");
}

/*
偶数グループ : 左->右にとる
奇数グループ : 右->左にとる
*/
void	get_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		usleep(100);
		get_fork_on_leftside(philo);
		// usleep(500);
		get_fork_on_rightside(philo);
	}
	else
	{
		usleep(100);
		get_fork_on_rightside(philo);
		// usleep(100);
		get_fork_on_leftside(philo);
	}
	philo->can_eat = true;
}

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

// とった順にフォークを置いてみる
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
	philo->can_eat = false;
}
