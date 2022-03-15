#include "philo.h"

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	*philo;
	t_error	err;

	err = NO_ERR;
	if (parse(argc, argv, &arg, &err) != 0
		|| make_philo(&philo, &arg, &err) != 0
		|| run_philo_thread(&philo, &err) != 0
		|| run_monitor_thread(&philo, &err) != 0
		|| wait_philo(&philo, &err) != 0
		|| wait_monitor(&philo, &err) != 0
		|| destroy_mutex(&philo, &err) != 0)
	{
		print_error(err);
		return (1);
	}
	return (0);
}
