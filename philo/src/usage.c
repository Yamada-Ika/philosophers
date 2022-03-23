/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:10:35 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 21:44:30 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	to_err(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
}

int	print_usage(void)
{
	to_err("Usage:\n");
	to_err("  ./philo number_of_philosophers ");
	to_err("time_to_die time_to_eat time_to_sleep ");
	to_err("[number_of_times_each_philosopher_must_eat]\n");
	return (FAILE);
}
