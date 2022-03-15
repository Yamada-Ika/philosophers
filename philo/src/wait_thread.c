#include "philo.h"

/**
 * @brief 哲学者達が食事を終えるのを待つ
 *
 */
int	wait_philo(t_philo **philo, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_join((*philo)[i].philo_id, NULL) != 0)
		{
			set_err(err, JOIN_THREAD);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief 哲学者のモニタリングが終了するのを待つ
 * 
 */
int	wait_monitor(t_philo **philo, t_error *err)
{
	if (pthread_join((*philo)[1].monitor_id, NULL) != 0)
	{
		set_err(err, JOIN_THREAD);
		return (1);
	}
	return (0);
}
