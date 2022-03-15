#include "philo.h"

static int	create_odd_group(t_philo **philo, t_attr *attr, t_error *err)
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

static int	create_even_group(t_philo **philo, t_attr *attr, t_error *err)
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

static void	wait_a_moment(void)
{
	usleep(200);
}

/**
 * @brief 並行して哲学者に食事させるため、複数スレッドを作成
 * @details 哲学者を偶数、奇数グループにわけ、先に奇数グループのスレッドを走らせている
 */
int	run_philo_thread(t_philo **philo, t_error *err)
{
	if (create_odd_group(philo, NULL, err) != 0)
		return (1);
	wait_a_moment();
	return (create_even_group(philo, NULL, err));
}

/**
 * @brief 哲学者の状態を監視するため
 * @details モニターのスレッドは一つだけ
 */
int	run_monitor_thread(t_philo **philo, t_error *err)
{
	if (pthread_create(&((*philo)[1].monitor_id), NULL,
		monitor, ((*philo))) != 0)
	{
		set_err(err, CREATE_THREAD);
		return (1);
	}
	return (0);
}
