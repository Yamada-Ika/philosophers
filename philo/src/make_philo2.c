/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:31 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/16 00:40:42 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_nomem(t_share *share)
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

void	set_share(t_share *share, t_arg *argt, t_error *err)
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

void	set_philo(t_philo *philo, size_t index, t_arg *argt, t_share *share)
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
