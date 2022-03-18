/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 03:24:02 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/19 03:26:59 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Kills already started threads when an error occurs
 * 
 * @details Wait an appropriate number of seconds so that
 *          the main thread does not terminate first
 */
void	kill_thread(t_philo *philo)
{
	set_end_dinner_flag(philo);
	usleep(1000000);
}
