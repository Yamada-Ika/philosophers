#include "philo.h"

// __attribute__((destructor))
// void	check_leak(void)
// {
// 	char	cmd[50];

// 	sprintf(cmd, "leaks %d", getpid());
// 	system(cmd);
// }

int	main(int argc, char *argv[])
{
	t_arg			arg;
	t_philo			*philo;
	t_error_kind	err;

	err = NO_ERR;
	if (validate_arg(argc, argv, &arg, &err) != 0
		|| make_philo(&philo, &arg, &err) != 0
		|| make_mutex(&philo, &err) != 0
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
