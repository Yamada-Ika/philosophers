#include "philo.h"

int	get_index(int index, int philos_number)
{
	if (index == 0)
		return (philos_number);
	else if (index == philos_number + 1)
		return (1);
	else
		return (index);
}

long long	get_timestamp(t_philo_info *philo)
{
	t_time		tv;
	long long	timestamp;

	if (gettimeofday(&tv, NULL) == 0)
	{
		pthread_mutex_lock(philo->mtx_for_time);
		timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		pthread_mutex_unlock(philo->mtx_for_time);
		return (timestamp);
	}
	return (0);
}

long long	get_timestamp_in_usec(t_philo_info *philo)
{
	t_time		tv;
	long long	timestamp;

	if (gettimeofday(&tv, NULL) == 0)
	{
		pthread_mutex_lock(philo->mtx_for_time);
		timestamp = tv.tv_sec * 1000000 + tv.tv_usec;
		pthread_mutex_unlock(philo->mtx_for_time);
		return (timestamp);
	}
	return (0);
}

bool	is_end_simulation(t_philo_info *philo)
{
	bool	res;

	pthread_mutex_lock(philo->mtx_for_status);
	res = (philo->sim_state->kind == END_SIMULATION);
	pthread_mutex_unlock(philo->mtx_for_status);
	return (res);
}

void	my_msleep(long long msec, t_philo_info *philo)
{
	long long	start;

	start = get_timestamp(philo);
	// while (!(philo->sim_state->kind == END_SIMULATION))
	while (!is_end_simulation(philo))
	{
		if (get_timestamp(philo) - start >= msec)
			return ;
		usleep(500);
	}
}

void	my_usleep(long long usec, t_philo_info *philo)
{
	long long	start;

	start = get_timestamp_in_usec(philo);
	// while (!(philo->sim_state->kind == END_SIMULATION))
	while (!is_end_simulation(philo))
	{
		if (get_timestamp_in_usec(philo) - start >= usec)
			return ;
		usleep(1);
	}
}

void	print_action(t_philo_info *philo, pthread_mutex_t *mutex, int philo_index, char *action)
{
	pthread_mutex_lock(mutex);
	printf("%lld %d", get_timestamp(philo), philo_index);
	printf(" %s\n", action);
	pthread_mutex_unlock(mutex);
}

size_t	ft_strlen(const char *s)
{
	size_t	s_len;

	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	return (s_len);
}

void	print_error(char *message)
{
	write(STDERR_FILENO, "Error: ", ft_strlen("Error: "));
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}
