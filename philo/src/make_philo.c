#include "philo.h"

typedef struct s_share
{
	bool			*is_end;
	t_mutex			*forks;
	t_mutex			*log;
	t_mutex			*state;
	t_mutex			*count;
	t_mutex			*time;
	t_mutex			*mtx_err;
	t_error_kind	*err;
	size_t			*full_num;
}	t_share;

static bool	is_nomem(t_share *share)
{
	return (share->forks == NULL
		|| share->is_end == NULL
		|| share->log == NULL
		|| share->state == NULL
		|| share->count == NULL
		|| share->time == NULL
		|| share->mtx_err == NULL
		|| share->full_num == NULL);
}

static void	set_share(t_share *share, t_arg *argt, t_error_kind *err)
{
	share->is_end = (bool *)ft_calloc(1, sizeof(bool));
	share->forks = (t_mutex *)ft_calloc(argt->num_of_philo + 1,
			sizeof(t_mutex));
	share->log = (t_mutex *)ft_calloc(1, sizeof(t_mutex));
	share->state = (t_mutex *)ft_calloc(1, sizeof(t_mutex));
	share->count = (t_mutex *)ft_calloc(1, sizeof(t_mutex));
	share->time = (t_mutex *)ft_calloc(1, sizeof(t_mutex));
	share->mtx_err = (t_mutex *)ft_calloc(1, sizeof(t_mutex));
	share->err = err;
	share->full_num = (size_t *)ft_calloc(1, sizeof(size_t));
	if (is_nomem(share))
		set_err(err, NO_MEM);
}

static void	set_philo(t_philo *philo, size_t index, t_arg *argt, t_share *share)
{
	philo->index = index;
	philo->philo_number = argt->num_of_philo;
	philo->time_to_eat = argt->time_to_eat;
	philo->time_to_sleep = argt->time_to_sleep;
	philo->time_to_die = argt->time_to_die;
	philo->must_eat_times = argt->must_eat_times;
	philo->eat_count = 0;
	philo->last_meal_time = get_timestamp();
	philo->is_end = share->is_end;
	philo->forks = share->forks;
	philo->full_num = share->full_num;
	philo->state = share->state;
	philo->log = share->log;
	philo->count = share->count;
	philo->time = share->time;
	philo->mtx_err = share->mtx_err;
	philo->err = share->err;
	if (argt->is_set_eat_cnt)
		philo->should_count_eat = true;
}

/**
 * @brief 各スレッドに渡す構造体の配列を作成する関数
 * 
 * @param philo 各スレッドに渡す構造体の配列
 * @param argt コマンドライン引数を格納している構造体
 * @param err エラーを格納する変数
 * @return int エラーが発生すると1を返し、それ以外は0
 */
int	make_philo(t_philo **philo, t_arg *argt, t_error_kind *err)
{
	t_share	share;
	size_t	i;

	*philo = (t_philo *)ft_calloc(argt->num_of_philo + 1, sizeof(t_philo));
	if (*philo == NULL)
	{
		set_err(err, NO_MEM);
		return (1);
	}
	set_share(&share, argt, err);
	if (is_err_occured(err))
		return (1);
	i = 1;
	while (i < argt->num_of_philo + 1)
	{
		set_philo(&(*philo)[i], i, argt, &share);
		i++;
	}
	return (0);
}
