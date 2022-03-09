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

void	print_action(pthread_mutex_t *mtx, int index, char *action)
{
	pthread_mutex_lock(mtx);
	printf("%lld %d", get_timestamp(), index);
	printf(" %s\n", action);
	pthread_mutex_unlock(mtx);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	print_error(char *message)
{
	write(STDERR_FILENO, "Error: ", ft_strlen("Error: "));
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	wait_all_thread(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(philo->state);
		if (*(philo->is_ready_thread))
		{
			pthread_mutex_unlock(philo->state);
			return ;
		}
		pthread_mutex_unlock(philo->state);
		my_usleep(10, philo);
	}
}

void	wait_even_group(t_philo *philo)
{
	if (philo->index % 2 == 1)
		return ;
	while (true)
	{
		pthread_mutex_lock(philo->state);
		if (*(philo->is_even_ready))
		{
			pthread_mutex_unlock(philo->state);
			return ;
		}
		pthread_mutex_unlock(philo->state);
		my_usleep(10, philo);
	}
}

// void	wait_odd_group(t_philo *philo)
// {
// 	if (philo->index % 2 == 0)
// 		return ;
// 	while (true)
// 	{
// 		pthread_mutex_lock(philo->state);
// 		if (*(philo->is_ready_thread))
// 		{
// 			pthread_mutex_unlock(philo->state);
// 			return ;
// 		}
// 		pthread_mutex_unlock(philo->state);
// 		my_usleep(100, philo);
// 	}
// }
