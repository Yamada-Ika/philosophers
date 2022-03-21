/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:26 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/21 19:13:47 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// __attribute__((destructor))
// static void destructor() {
// 	char buf[100];

// 	sprintf(buf, "leaks -q %d", getpid());
// 	system(buf);
// }

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	*philo;
	t_error	err;

	err = NO_ERR;
	if (parse(argc, argv, &arg, &err) != 0
		|| new_philo(&philo, &arg, &err) != 0)
	{
		return (print_error(err));
	}
	if (init_philo(philo, &arg, &err) != 0
		|| run_philo_thread(&philo, &err) != 0
		|| run_monitor_thread(&philo, &err) != 0
		|| wait_philo(&philo, &err) != 0
		|| wait_monitor(&philo, &err) != 0
		|| destroy_mutex(&philo, &err) != 0)
	{
		destroy_philo(philo);
		return (print_error(err));
	}
	destroy_philo(philo);
	return (0);
}
