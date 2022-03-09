#include "philo.h"

// __attribute__((destructor))
// void	check_leak(void)
// {
// 	char	cmd[50];

// 	sprintf(cmd, "leaks %d", getpid());
// 	system(cmd);
// }

void	debug_arg(t_arg *argt)
{
	fprintf(stderr, "number of philo  : %d\n", argt->number_of_philosophers);
	fprintf(stderr, "time to die      : %d\n", argt->time_to_die);
	fprintf(stderr, "time to eat      : %d\n", argt->time_to_eat);
	fprintf(stderr, "time to sleep    : %d\n", argt->time_to_sleep);
	fprintf(stderr, "must eat times   : %d\n", argt->number_of_times_each_philosopher_must_eat);
}

int	validate_arg(int argc, char *argv[], t_arg *argt, t_error_kind *error_num)
{
	if (argc == 5 || argc == 6)
	{
		argt->number_of_philosophers = atoi(argv[1]);
		if (argt->number_of_philosophers == 0)
		{
			*error_num = MORE_PHILO;
			return (1);
		}
		argt->time_to_die = atoi(argv[2]);
		argt->time_to_eat = atoi(argv[3]);
		argt->time_to_sleep = atoi(argv[4]);
		if (argc == 6)
			argt->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		else
			argt->number_of_times_each_philosopher_must_eat = -1;
		// debug_arg(argt);
	}
	else
	{
		*error_num = ARG_NUM;
		return (1);
	}
	return (0);
}

void	error(t_error_kind kind)
{
	if (kind == MORE_PHILO)
		printf("error: Input more philosophers\n");
	else if (kind == ARG_NUM)
		printf("error: Argument number is 4 or 5\n");
	else if (kind == MEMORY)
		printf("error: Failed to memory allocate\n");
	else if (kind == INIT_MTX)
		printf("error: Failed to initialize mutex\n");
	else if (kind == DESTROY_MTX)
		printf("error: Failed to destroy mutex\n");
	else if (kind == LOCK_MTX)
		printf("error: Failed to lock mutex\n");
	else if (kind == UNLOCK_MTX)
		printf("error: Failed to unlock mutex\n");
	else if (kind == CREATE_THREAD)
		printf("error: Failed to create thread\n");
	else if (kind == DETACH_PHILO)
		printf("error: Failed to detach thread\n");
	else if (kind == JOIN_THREAD)
		printf("error: Failed to join thread\n");
	else
		printf("error: %d Unknown error\n", kind);
}

int	main(int argc, char *argv[])
{
	t_arg			arg;
	t_philo			*philo;
	t_error_kind	error_num;

	error_num = -1;
	if (validate_arg(argc, argv, &arg, &error_num) != 0
		|| init_philo(&philo, &arg, &error_num) != 0
		|| init_mutex(&philo, &error_num) != 0
		|| create_thread(&philo, &error_num) != 0
		|| detach_philo(&philo, &error_num) != 0
		|| wait_monitor(&philo, &error_num) != 0)
	{
		error(error_num);
		return (1);
	}
	return (0);
}
