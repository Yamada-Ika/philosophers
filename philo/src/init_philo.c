/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:29 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 21:41:51 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_nomem(t_share *share)
{
	return (share->forks == NULL
		|| share->is_end == NULL
		|| share->mtxs == NULL
		|| share->full_num == NULL);
}

static void	set_share(t_share *share, t_arg *argt, t_error *err)
{
	share->is_end = (bool *)ft_calloc(1, sizeof(bool));
	share->forks = (t_mutex *)ft_calloc(argt->num_of_philo + 1,
			sizeof(t_mutex));
	share->mtxs = (t_mutex *)ft_calloc(MTXS_N, sizeof(t_mutex));
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
	philo->full_num = share->full_num;
	philo->forks = share->forks;
	philo->mtxs = share->mtxs;
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
		return (FAILE);
	return (set_obj_to_philo(philo, argt, &share, err));
}
