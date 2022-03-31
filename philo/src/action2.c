/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:28:53 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/30 16:35:10 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	update_last_mealtime(t_philo *philo)
{
	// if (mutex_lock(&philo->mtxes[TIME], &philo->mtxes[ERR], philo->err) == FAIL)
	// 	return (FAIL);
	philo->last_meal_time = get_timestamp();
	return (SUCCESS);
	// return (mutex_unlock(&philo->mtxes[TIME], &philo->mtxes[ERR], philo->err));
}

int	incre_full_philo(t_philo *p)
{
	if (mutex_lock(&p->mtxes[COUNT], &p->mtxes[ERR], p->err) == FAIL)
		return (FAIL);
	*(p->full_num) += 1;
	return (mutex_unlock(&p->mtxes[COUNT], &p->mtxes[ERR], p->err));
}

int	still_hungry(t_philo *philo)
{
	return (!philo->is_full
		&& philo->should_count_eat
		&& philo->eat_count >= philo->must_eat_times);
}
