#include "philo.h"

void	get_fork_on_leftside(t_philo_info *philo)
{
	int	cur_index = philo->index;
	int	leftside_index = get_index(cur_index + 1, philo->philo_number);

	// if (philo->status->is_someone_dead)
	if (is_somephilo_dead(philo))
		return ;
	if (philo->forks[leftside_index])
	{
		philo->forks[leftside_index] = false;
		philo->has_fork_on_lefthand = true;
		printf("%lld %d has taken a left-side fork\n", get_timestamp(), philo->index);
	}
}

void	get_fork_on_rightside(t_philo_info *philo)
{
	int	cur_index = philo->index;
	int	rightside_index = cur_index;

	// if (philo->status->is_someone_dead)
	if (is_somephilo_dead(philo))
		return ;
	if (philo->forks[rightside_index])
	{
		philo->forks[rightside_index] = false;
		philo->has_fork_on_righthand = true;
		printf("%lld %d has taken a right-side fork\n", get_timestamp(), philo->index);
	}
}

/*
偶数グループ : 左->右にとる
奇数グループ : 右->左にとる
*/
void	get_forks(t_philo_info *philo)
{
	// if (philo->status->is_someone_dead)
	if (is_somephilo_dead(philo))
		return ;
	if (philo->is_even_group)
	{
		// while (!philo->has_fork_on_lefthand && !philo->status->is_someone_dead)
		while (!philo->has_fork_on_lefthand && !is_somephilo_dead(philo))
			get_fork_on_leftside(philo);
		// while (!philo->has_fork_on_righthand && !philo->status->is_someone_dead)
		while (!philo->has_fork_on_righthand && !is_somephilo_dead(philo))
			get_fork_on_rightside(philo);
	}
	else
	{
		// while (!philo->has_fork_on_righthand && !philo->status->is_someone_dead)
		while (!philo->has_fork_on_righthand && !is_somephilo_dead(philo))
			get_fork_on_rightside(philo);
		// while (!philo->has_fork_on_lefthand && !philo->status->is_someone_dead)
		while (!philo->has_fork_on_lefthand && !is_somephilo_dead(philo))
			get_fork_on_leftside(philo);
	}
}

void	put_forks(t_philo_info *philo)
{
	int	rightside_index;
	int	leftside_index;

	philo->has_fork_on_lefthand = false;
	philo->has_fork_on_righthand = false;
	rightside_index = philo->index;
	leftside_index = get_index(philo->index + 1, philo->philo_number);
	philo->forks[leftside_index] = true;
	philo->forks[rightside_index] = true;
}
