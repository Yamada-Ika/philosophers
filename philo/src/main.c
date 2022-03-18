/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:26 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/19 01:10:14 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__attribute__((destructor))
static void destructor() {
	char buf[100];

	sprintf(buf, "leaks -q %d", getpid());
	system(buf);
}

void	destroy_philo(t_philo *philo)
{
	free(philo[1].is_end);
	free(philo[1].forks);
	free(philo[1].log);
	free(philo[1].state);
	free(philo[1].count);
	free(philo[1].time);
	free(philo[1].mtx_err);
	free(philo[1].full_num);
	free(philo);
}

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	*philo;
	t_error	err;

	err = NO_ERR;
	if (parse(argc, argv, &arg, &err) != 0)
	{
		print_error(err);
		return (1);
	}
	if (make_philo(&philo, &arg, &err) != 0
		|| run_philo_thread(&philo, &err) != 0
		|| run_monitor_thread(&philo, &err) != 0
		|| wait_philo(&philo, &err) != 0
		|| wait_monitor(&philo, &err) != 0
		|| destroy_mutex(&philo, &err) != 0)
	{
		destroy_philo(philo);
		print_error(err);
		return (1);
	}
	destroy_philo(philo);
	return (0);
}
