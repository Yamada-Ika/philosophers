#include "philo.h"

typedef struct s_share
{
	t_mutex	*forks;
	t_mutex	*log;
	t_mutex	*state;
	t_mutex	*count;
	t_mutex	*time;
	size_t	*full_num;
	bool	*is_ready_thread;
	bool	*is_even_ready;
	bool	*is_init;
	bool	*is_end;
}	t_share;

static bool	is_nomem(t_share *share)
{
	return (share->forks == NULL
		|| share->log == NULL
		|| share->state == NULL
		|| share->count == NULL
		|| share->time == NULL
		|| share->full_num == NULL
		|| share->is_ready_thread == NULL
		|| share->is_even_ready == NULL
		|| share->is_init == NULL
		|| share->is_end == NULL);
}

static void	set_share_obj(t_share *share, t_arg *argt, t_error_kind *err)
{
	share->forks = (t_mutex *)calloc(argt->num_of_philo + 1, sizeof(t_mutex));
	share->log = (t_mutex *)calloc(1, sizeof(t_mutex));
	share->state = (t_mutex *)calloc(1, sizeof(t_mutex));
	share->count = (t_mutex *)calloc(1, sizeof(t_mutex));
	share->time = (t_mutex *)calloc(1, sizeof(t_mutex));
	share->full_num = (size_t *)calloc(1, sizeof(size_t));
	share->is_ready_thread = (bool *)calloc(1, sizeof(bool));
	share->is_even_ready = (bool *)calloc(1, sizeof(bool));
	share->is_init = (bool *)calloc(1, sizeof(bool));
	share->is_end = (bool *)calloc(1, sizeof(bool));
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
	philo->forks = share->forks;
	philo->full_num = share->full_num;
	philo->is_ready_thread = share->is_ready_thread;
	philo->is_even_ready = share->is_even_ready;
	philo->is_init = share->is_init;
	philo->is_end = share->is_end;
	philo->state = share->state;
	philo->log = share->log;
	philo->count = share->count;
	philo->time = share->time;
	if (argt->is_set_eat_cnt)
		philo->should_count_eat = true;
}

int	make_philo(t_philo **philo, t_arg *argt, t_error_kind *err)
{
	t_share	share;
	size_t	i;

	*philo = (t_philo *)calloc(argt->num_of_philo + 1, sizeof(t_philo));
	if (*philo == NULL)
	{
		set_err(err, NO_MEM);
		return (1);
	}
	set_share_obj(&share, argt, err);
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
