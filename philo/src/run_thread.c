#include "philo.h"

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

/**
 * @brief 哲学者の人数分、スレッドを作成する関数
 * @details 哲学者を偶数、奇数グループにわけ、先に奇数グループのスレッドを走らせている
 * 
 * @param philo 各スレッドに渡す構造体の配列
 * @param err エラーを格納する変数
 * @return int エラーが発生すると1を返し、それ以外は0
 */
int	run_philo_thread(t_philo **philo, t_error_kind *err)
{
	if (create_odd_group(philo, NULL, err) != 0)
		return (1);
	usleep(200);
	if (create_even_group(philo, NULL, err) != 0)
		return (1);
	return (0);
}

/**
 * @brief 哲学者を監視するスレッドを作成する関数
 * @details モニターのスレッドは一つだけ
 * 
 * @param philo 全ての哲学者を監視するので、構造体の配列をスレッドに渡す
 * @param err エラーを格納する変数
 * @return int エラーが発生すると1を返し、それ以外は0
 */
int	run_monitor_thread(t_philo **philo, t_error_kind *err)
{
	if (pthread_create(&((*philo)[1].monitor_id), NULL,
		monitor, ((*philo))) != 0)
	{
		set_err(err, CREATE_THREAD);
		return (1);
	}
	return (0);
}
