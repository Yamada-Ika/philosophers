#include "philo.h"

void	get_fork_on_leftside(t_philo_info *philo)
{
	int	cur_index = philo->index;
	int	leftside_index = get_index(cur_index + 1, philo->philo_number);
	bool	res;

	if (is_end_simulation(philo))
		return ;
	pthread_mutex_lock(philo->mtx_for_fork);
	res = philo->forks[leftside_index];
	pthread_mutex_unlock(philo->mtx_for_fork);
	if (res)
	{
		pthread_mutex_lock(philo->mtx_for_fork);
		philo->forks[leftside_index] = false;
		pthread_mutex_unlock(philo->mtx_for_fork);
		if (philo->own_state == HOLD_FORK_IN_RIGHT)
			philo->own_state = READY_TO_EAT;
		if (philo->own_state == HOLD_NOTHING)
			philo->own_state = HOLD_FORK_IN_LEFT;
		print_action(philo->mtx_for_print, philo->index, "has taken a fork");
	}
}

void	get_fork_on_rightside(t_philo_info *philo)
{
	int	cur_index = philo->index;
	int	rightside_index = cur_index;
	bool	res;

	if (is_end_simulation(philo))
		return ;
	pthread_mutex_lock(philo->mtx_for_fork);
	res = philo->forks[rightside_index];
	pthread_mutex_unlock(philo->mtx_for_fork);
	if (res)
	{
		pthread_mutex_lock(philo->mtx_for_fork);
		philo->forks[rightside_index] = false;
		pthread_mutex_unlock(philo->mtx_for_fork);
		if (philo->own_state == HOLD_FORK_IN_LEFT)
			philo->own_state = READY_TO_EAT;
		if (philo->own_state == HOLD_NOTHING)
			philo->own_state = HOLD_FORK_IN_RIGHT;
		print_action(philo->mtx_for_print, philo->index, "has taken a fork");
	}
}

/*
偶数グループ : 左->右にとる
奇数グループ : 右->左にとる
*/
void	get_forks(t_philo_info *philo)
{
	if (is_end_simulation(philo))
		return ;
	if (philo->index % 2 == 0)
	{
		get_fork_on_leftside(philo);
		usleep(100);
		get_fork_on_rightside(philo);
	}
	else
	{
		get_fork_on_rightside(philo);
		usleep(100);
		get_fork_on_leftside(philo);
	}
}

void	put_fork_on_leftside(t_philo_info *philo)
{
	int	leftside_index;

	leftside_index = get_index(philo->index + 1, philo->philo_number);
	pthread_mutex_lock(philo->mtx_for_fork);
	philo->forks[leftside_index] = true;
	pthread_mutex_unlock(philo->mtx_for_fork);
	if (philo->own_state == HOLD_FORK_IN_LEFT)
		philo->own_state = HOLD_NOTHING;
	if (philo->own_state == READY_TO_EAT)
		philo->own_state = HOLD_FORK_IN_RIGHT;
}

void	put_fork_on_rightside(t_philo_info *philo)
{
	int	rightside_index;

	rightside_index = philo->index;
	pthread_mutex_lock(philo->mtx_for_fork);
	philo->forks[rightside_index] = true;
	pthread_mutex_unlock(philo->mtx_for_fork);
	if (philo->own_state == HOLD_FORK_IN_RIGHT)
		philo->own_state = HOLD_NOTHING;
	if (philo->own_state == READY_TO_EAT)
		philo->own_state = HOLD_FORK_IN_LEFT;
}

void	put_forks(t_philo_info *philo)
{
	put_fork_on_leftside(philo);
	put_fork_on_rightside(philo);
	// pthread_mutex_lock(philo->mtx_for_status);
	// philo->sim_state->kind = HOLD_NOTHING;
	// pthread_mutex_unlock(philo->mtx_for_status);
}
