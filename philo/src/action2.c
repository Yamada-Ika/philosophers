/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:28:53 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 21:29:21 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	update_last_mealtime(t_philo *philo)
{
	if (mutex_lock(&philo->mtxs[TIME], &philo->mtxs[ERR], philo->err) != 0)
		return (1);
	philo->last_meal_time = get_timestamp();
	return (mutex_unlock(&philo->mtxs[TIME], &philo->mtxs[ERR], philo->err));
}

int	incre_full_philo(t_philo *philo)
{
	if (mutex_lock(&philo->mtxs[COUNT], &philo->mtxs[ERR], philo->err) != 0)
		return (1);
	*(philo->full_num) += 1;
	return (mutex_unlock(&philo->mtxs[COUNT], &philo->mtxs[ERR], philo->err));
}

int	still_hungry(t_philo *philo)
{
	return (!philo->is_full
		&& philo->should_count_eat
		&& philo->eat_count >= philo->must_eat_times);
}
