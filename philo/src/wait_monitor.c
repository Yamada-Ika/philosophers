#include "philo.h"

int	wait_monitor(t_philo **philo, t_error_kind *error_num)
{
	if (pthread_join((*philo)[1].monitor_id, NULL) != 0)
	{
		*error_num = JOIN_THREAD;
		return (1);
	}
	return (0);
}
