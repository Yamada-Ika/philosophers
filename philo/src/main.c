#include "philo.h"

// __attribute__((destructor))
// void	check_leak(void)
// {
// 	char	cmd[50];

// 	sprintf(cmd, "leaks %d", getpid());
// 	system(cmd);
// }

void	debug_arg(t_arg_info *argt)
{
	fprintf(stderr, "number of philo : %d\n", argt->number_of_philosophers);
	fprintf(stderr, "time to die     : %d\n", argt->time_to_die);
	fprintf(stderr, "time to eat     : %d\n", argt->time_to_eat);
	fprintf(stderr, "time to sleep   : %d\n", argt->time_to_sleep);
}

void	get_arg(int argc, char *argv[], t_arg_info *argt)
{
	if (argc == 5 || argc == 6)
	{
		argt->number_of_philosophers = atoi(argv[1]);
		if (argt->number_of_philosophers == 0)
		{
			argt->is_invalid_arg = true;
			return ;
		}
		argt->time_to_die = atoi(argv[2]);
		argt->time_to_eat = atoi(argv[3]);
		argt->time_to_sleep = atoi(argv[4]);
		if (argc == 6)
			argt->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		argt->is_invalid_arg = false;
		// debug_arg(argt);
	}
	else
		argt->is_invalid_arg = true;
}

int	main(int argc, char *argv[])
{
	t_arg_info	arg;
	t_philo_info	*philo;
	void	*monitor_status;

	get_arg(argc, argv, &arg);
	if (arg.is_invalid_arg)
	{
		fprintf(stderr, "Error: Invalid argument\n");
		return (0);
	}
	philo = init_philo(&arg);
	if (!can_init_mutex(philo))
	{
		fprintf(stderr, "Error: Failed to initialize mutex\n");
		return (1);
	}
	if (!can_create_thread(philo))
	{
		fprintf(stderr, "Error: Failed to create thread\n");
		return (1);
	}
	for (int i = 1; i < philo[1].philo_number + 1; i++)
	{
		pthread_join(philo[i].monitor_id, &monitor_status);
		pthread_join(philo[i].philo_id, NULL);
	}
	// fprintf(stderr, "finish philo\n");
	if ((bool)monitor_status)
	{
		can_destroy_mutex(philo);
		return (0);
	}
	if (!can_destroy_mutex(philo))
	{
		fprintf(stderr, "Error: Failed to destroy mutex\n");
		return (1);
	}
	return (0);
}
