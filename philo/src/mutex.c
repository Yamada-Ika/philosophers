#include "philo.h"

/**
 * @brief mutexを初期化する関数
 * 
 * @param philo mutexを含む構造体の配列
 * @param err エラーを格納する変数
 * @return int エラーが発生すると1を返し、それ以外は0
 */
int	make_mutex(t_philo **philo, t_error_kind *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_mutex_init(&((*philo)[1].forks[i]), NULL) != 0)
		{
			set_err(err, INIT_MTX);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(((*philo)[1].log), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].state), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].count), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].time), NULL) != 0
		|| pthread_mutex_init(((*philo)[1].mtx_err), NULL) != 0)
	{
		set_err(err, INIT_MTX);
		return (1);
	}
	return (0);
}

/**
 * @brief mutexを破壊する関数
 * 
 * @param philo 各スレッドに渡した構造体の配列
 * @param err エラーを格納する変数
 * @return int エラーが発生すると1を返し、それ以外は0
 */
int	destroy_mutex(t_philo **philo, t_error_kind *err)
{
	size_t	i;

	i = 1;
	while (i < (*philo)[1].philo_number + 1)
	{
		if (pthread_mutex_destroy(&(*philo)[1].forks[i]) != 0)
		{
			set_err(err, DESTROY_MTX);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_destroy((*philo)[1].log) != 0
		|| pthread_mutex_destroy((*philo)[1].state) != 0
		|| pthread_mutex_destroy((*philo)[1].count) != 0
		|| pthread_mutex_destroy((*philo)[1].time) != 0
		|| pthread_mutex_destroy((*philo)[1].mtx_err) != 0)
	{
		set_err(err, DESTROY_MTX);
		return (1);
	}
	return (0);
}

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
