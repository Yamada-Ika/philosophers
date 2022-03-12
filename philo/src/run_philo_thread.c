#include "philo.h"

// static int	set_thread_attr(t_attr *attr, int kind, t_error_kind *err)
// {
// 	if (pthread_attr_init(attr) != 0)
// 	{
// 		set_err(err, INIT_ATTR);
// 		return (1);
// 	}
// 	if (pthread_attr_setdetachstate(attr, kind) != 0)
// 	{
// 		set_err(err, ADD_ATTR);
// 		return (1);
// 	}
// 	return (0);
// }

static int	create_odd_group(t_philo **philo, t_attr *attr, t_error_kind *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_create(&((*philo)[i].philo_id), attr,
			do_action, &((*philo)[i])) != 0)
		{
			set_err(err, CREATE_THREAD);
			return (1);
		}
		i += 2;
	}
	return (0);
}

static int	create_even_group(t_philo **philo, t_attr *attr, t_error_kind *err)
{
	size_t	i;

	i = 2;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_create(&((*philo)[i].philo_id), attr,
			do_action, &((*philo)[i])) != 0)
		{
			set_err(err, CREATE_THREAD);
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	run_philo_thread(t_philo **philo, t_error_kind *err)
{
	// t_attr	attr;

	// if (set_thread_attr(&attr, PTHREAD_CREATE_DETACHED, err) != 0)
	// 	return (1);
	// if (create_odd_group(philo, &attr, err) != 0)
	// 	return (1);
	// usleep(200);
	// if (create_even_group(philo, &attr, err) != 0)
	// 	return (1);
	if (create_odd_group(philo, NULL, err) != 0)
		return (1);
	usleep(200);
	if (create_even_group(philo, NULL, err) != 0)
		return (1);
	return (0);
}
