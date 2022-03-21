/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:29 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/21 18:50:30 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	set_share(t_share *share, t_arg *argt, t_error *err)
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
	philo->num = argt->num_of_philo;
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

static int	set_obj_to_philo(t_philo *philo, t_arg *argt,
	t_share *share, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < argt->num_of_philo + 1)
	{
		set_philo(&philo[i], i, argt, share);
		i++;
	}
	return (init_mutex(philo, err));
}

int	init_philo(t_philo *philo, t_arg *argt, t_error *err)
{
	t_share	share;

	set_share(&share, argt, err);
	if (is_err_occured(err))
		return (1);
	return (set_obj_to_philo(philo, argt, &share, err));
}
