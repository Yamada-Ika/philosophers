#include "philo.h"

int	mutex_lock(t_mutex *mtx, t_mutex *mtx_err, t_error_kind *err)
{
	if (pthread_mutex_lock(mtx) != 0)
	{
		pthread_mutex_lock(mtx_err);
		set_err(err, LOCK_MTX);
		pthread_mutex_unlock(mtx_err);
		return (1);
	}
	return (0);
}

int	mutex_unlock(t_mutex *mtx, t_mutex *mtx_err, t_error_kind *err)
{
	if (pthread_mutex_unlock(mtx) != 0)
	{
		pthread_mutex_lock(mtx_err);
		set_err(err, UNLOCK_MTX);
		pthread_mutex_unlock(mtx_err);
		return (1);
	}
	return (0);
}
