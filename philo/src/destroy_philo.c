/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:51:50 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/24 00:09:32 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo(t_philo *philos)
{
	free(philos[1].forks);
	free(philos[1].mtxes);
	free(philos[1].is_end);
	free(philos[1].full_num);
	free(philos);
}
