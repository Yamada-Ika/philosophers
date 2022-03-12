#include "philo.h"

/**
 * @brief モニターのスレッドが終了するのを待つ関数
 * 
 * @param philo 各スレッドに渡した構造体の配列
 * @param err エラーを格納する変数
 * @return int エラーが発生すると1を返し、それ以外は0
 */
int	wait_monitor(t_philo **philo, t_error_kind *err)
{
	if (pthread_join((*philo)[1].monitor_id, NULL) != 0)
	{
		set_err(err, JOIN_THREAD);
		return (1);
	}
	return (0);
}

/**
 * @brief 哲学者のスレッドが終了するのを待つ関数
 * 
 * @param philo 各スレッドに渡した構造体の配列
 * @param err エラーを格納する変数
 * @return int エラーが発生すると1を返し、それ以外は0
 */
int	wait_philo(t_philo **philo, t_error_kind *err)
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
