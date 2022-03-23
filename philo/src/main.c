/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:26 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 22:50:49 by iyamada          ###   ########.fr       */
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
	t_philo	*philo;
	t_error	err;

	err = NO_ERR;
	if (parse(argc, argv, &arg, &err) == FAILE)
	{
		print_error(err);
		return (print_usage());
	}
	if (new_philo(&philo, &arg, &err) == FAILE)
		return (print_error(err));
	if (init_philo(philo, &arg, &err) == FAILE
		|| run_philo_thread(philo, &err) == FAILE
		|| run_monitor_thread(philo, &err) == FAILE
		|| wait_philo(philo, &err) == FAILE
		|| wait_monitor(philo, &err) == FAILE
		|| destroy_mutex(philo, &err) == FAILE)
	{
		destroy_philo(philo);
		return (print_error(err));
	}
	destroy_philo(philo);
	return (SUCCESS);
}
