/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:26 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/24 00:24:23 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_usage(void);

// __attribute__((destructor))
// static void destructor() {
// 	char buf[100];

// 	sprintf(buf, "leaks -q %d", getpid());
// 	system(buf);
// }

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	*philos;
	t_error	err;

	err = NO_ERR;
	if (parse(argc, argv, &arg, &err) == FAIL)
	{
		print_error(err);
		return (print_usage());
	}
	if (new_philo(&philos, &arg, &err) == FAIL)
		return (print_error(err));
	if (init_philo(philos, &arg, &err) == FAIL
		|| run_philo_thread(philos, &err) == FAIL
		|| run_monitor_thread(philos, &err) == FAIL
		|| wait_philo(philos, &err) == FAIL
		|| wait_monitor(philos, &err) == FAIL
		|| destroy_mutex(philos, &err) == FAIL)
	{
		destroy_philo(philos);
		return (print_error(err));
	}
	destroy_philo(philos);
	return (SUCCESS);
}
