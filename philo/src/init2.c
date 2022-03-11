#include "philo.h"

int	init_mutex(t_philo **philo, t_error_kind *error_num)
{
	int	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_mutex_init(&((*philo)[1].forks[i]), NULL) != 0)
		{
			*error_num = INIT_MTX;
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(((*philo)[1].log), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].state), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].count), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].time), NULL) != 0)
	{
		*error_num = INIT_MTX;
		return (1);
	}
	return (0);
}

// int	destroy_mutex(t_philo **philo, t_error_kind *error_num)
// {
// 	int	i;

// 	i = 1;
// 	while (i < (*philo)[1].philo_number + 1)
// 	{
// 		if (pthread_mutex_destroy(&((*philo)[1].forks[i])) != 0)
// 		{
// 			*error_num = DESTROY_MTX;
// 			return (1);
// 		}
// 			return (false);
// 		i++;
// 	}
// 	if (pthread_mutex_destroy((*philo)[1].log) != 0
// 		|| pthread_mutex_destroy((*philo)[1].state) != 0)
// 	{
// 		*error_num = DESTROY_MTX;
// 		return (1);
// 	}
// 	return (0);
// }

int	create_thread(t_philo **philo, t_error_kind *error_num)
{
	int	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_create(&((*philo)[i].philo_id), NULL, do_action, &((*philo)[i])) != 0)
		{
			*error_num = CREATE_THREAD;
			return (1);
		}
		i += 2;
		// i++;
	}
	usleep(200);
	i = 2;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_create(&((*philo)[i].philo_id), NULL, do_action, &((*philo)[i])) != 0)
		{
			*error_num = CREATE_THREAD;
			return (1);
		}
		i += 2;
	}
	if (pthread_create(&((*philo)[1].monitor_id), NULL, monitor, ((*philo))) != 0)
	{
		*error_num = CREATE_THREAD;
		return (1);
	}
	return (0);
}

int	detach_philo(t_philo **philo, t_error_kind *error_num)
{
	int	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_detach((*philo)[i].philo_id) != 0)
		{
			*error_num = DETACH_PHILO;
			return (1);
		}
		i++;
	}
	return (0);
}

int	wait_monitor(t_philo **philo, t_error_kind *error_num)
{
	if (pthread_join((*philo)[1].monitor_id, NULL) != 0)
	{
		*error_num = JOIN_THREAD;
		return (1);
	}
	return (0);
}
