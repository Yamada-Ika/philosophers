#include "philo.h"

int	run_monitor_thread(t_philo **philo, t_error_kind *error_num)
{
	if (pthread_create(&((*philo)[1].monitor_id), NULL,
		monitor, ((*philo))) != 0)
	{
		*error_num = CREATE_THREAD;
		return (1);
	}
	return (0);
}
