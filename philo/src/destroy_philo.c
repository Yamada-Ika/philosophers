/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:51:50 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 21:40:34 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo(t_philo *philo)
{
	free(philo[1].forks);
	free(philo[1].mtxs);
	free(philo[1].is_end);
	free(philo[1].full_num);
	free(philo);
}
