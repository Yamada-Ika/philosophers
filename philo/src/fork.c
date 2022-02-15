#include "philo.h"

void	get_fork_on_leftside(t_philo_info *philo)
{
	int	cur_index = philo->index;
	int	leftside_index = get_index(cur_index + 1, philo->philo_number);

	if (is_somephilo_dead(philo))
		return ;
	pthread_mutex_lock(philo->mutex);
	if (philo->forks[leftside_index])
	{
		philo->forks[leftside_index] = false;
		philo->has_fork_on_lefthand = true;
		printf("%lld %d has taken a fork\n", get_timestamp(), philo->index);
	}
	pthread_mutex_unlock(philo->mutex);
}

void	get_fork_on_rightside(t_philo_info *philo)
{
	int	cur_index = philo->index;
	int	rightside_index = cur_index;

	if (is_somephilo_dead(philo))
		return ;
	pthread_mutex_lock(philo->mutex);
	if (philo->forks[rightside_index])
	{
		philo->forks[rightside_index] = false;
		philo->has_fork_on_righthand = true;
		printf("%lld %d has taken a fork\n", get_timestamp(), philo->index);
	}
	pthread_mutex_unlock(philo->mutex);
}

/*
偶数グループ : 左->右にとる
奇数グループ : 右->左にとる
*/
void	get_forks(t_philo_info *philo)
{
	if (is_somephilo_dead(philo))
		return ;
	if (philo->is_even_group)
	{
		get_fork_on_leftside(philo);
		get_fork_on_rightside(philo);
	}
	else
	{
		get_fork_on_rightside(philo);
		get_fork_on_leftside(philo);
	}
}

void	put_fork_on_leftside(t_philo_info *philo)
{
	int	leftside_index;

	philo->has_fork_on_lefthand = false;
	leftside_index = get_index(philo->index + 1, philo->philo_number);
	philo->forks[leftside_index] = true;
}

void	put_fork_on_rightside(t_philo_info *philo)
{
	int	rightside_index;

	philo->has_fork_on_righthand = false;
	rightside_index = philo->index;
	philo->forks[rightside_index] = true;
}

void	put_forks(t_philo_info *philo)
{
	put_fork_on_leftside(philo);
	put_fork_on_rightside(philo);
}
