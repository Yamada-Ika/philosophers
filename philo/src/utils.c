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

long long	get_timestamp(void)
{
	t_time	tv;

	if (gettimeofday(&tv, NULL) == 0)
	{
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	}
	return (0);
}

bool	is_somephilo_dead(t_philo_info *philo)
{
	bool	res;

	pthread_mutex_lock(philo->mtx_for_status);
	res = (philo->sim_state->kind == SOMEONE_DEAD);
	pthread_mutex_unlock(philo->mtx_for_status);
	return (res);
}


long long	get_timestamp_in_usec(void)
{
	t_time	tv;

	if (gettimeofday(&tv, NULL) == 0)
	{
		// printf("sec  : %zu\n", tv.tv_sec * 1000000);
		// printf("usec : %d\n", tv.tv_usec);
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	}
	return (0);
}

void	my_msleep(long long msec, t_philo_info *philo)
{
	long long	start;

	start = get_timestamp();
	while (!(philo->sim_state->kind == SOMEONE_DEAD))
	{
		// if (get_timestamp() - start >= msec - 1)
		if (get_timestamp() - start >= msec)
			return ;
		usleep(500);
	}
}

void	my_usleep(long long usec, t_philo_info *philo)
{
	long long	start;

	start = get_timestamp_in_usec();
	while (!(philo->sim_state->kind == SOMEONE_DEAD))
	{
		if (get_timestamp_in_usec() - start >= usec)
			return ;
		usleep(1);
	}
}

void	print_action(pthread_mutex_t *mutex, int philo_index, char *action)
{
	pthread_mutex_lock(mutex);
	printf("%lld %d", get_timestamp(), philo_index);
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
