#include "philo.h"

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
		argt->time_to_die = atoi(argv[2]);
		argt->time_to_eat = atoi(argv[3]);
		argt->time_to_sleep = atoi(argv[4]);
		if (argc == 6)
			argt->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		argt->is_invalid_arg = false;
		debug_arg(argt);
	}
	else
		argt->is_invalid_arg = true;
}

void	*monitor(void *argp)
{
	t_philo_info	*philo;

	philo = (t_philo_info *)argp;
	while (true)
	{
		long long cur_time = get_timestamp();
		if (get_timestamp() - philo->last_meal_time > philo->time_to_die)
		{
			printf("dead time: %lld\n", cur_time);
			break ;
		}
	}
	// philo->is_died = true;
	pthread_exit((void *)true);
}

t_philo_info	*init_philo(t_arg_info *arg)
{
	t_philo_info	*philo;
	bool	*forks;
	int	i;

	philo = (t_philo_info *)calloc(arg->number_of_philosophers + 1, sizeof(t_philo_info));
	forks = (bool *)calloc(arg->number_of_philosophers + 1, sizeof(bool));
	i = 1;
	while (i < arg->number_of_philosophers + 1)
	{
		forks[i] = true;
		philo[i].index = i;
		philo[i].has_fork_on_lefthand = false;
		philo[i].has_fork_on_righthand = false;
		philo[i].forks = forks;
		if (i % 2 == 0)
			philo[i].is_even_group = true;
		else
			philo[i].is_even_group = false;
		philo[i].philo_number = arg->number_of_philosophers;
		philo[i].time_to_eat = arg->time_to_eat;
		philo[i].time_to_sleep = arg->time_to_sleep;
		philo[i].time_to_die = arg->time_to_die;
		philo[i].last_meal_time = get_timestamp();
		i++;
	}
	return (philo);
}

int	main(int argc, char *argv[])
{
	t_arg_info	arg;
	t_philo_info	*philo;
	bool	is_someone_died;

	is_someone_died = false;
	get_arg(argc, argv, &arg);
	if (arg.is_invalid_arg)
	{
		fprintf(stderr, "Error: Invalid argument\n");
		return (0);
	}
	philo = init_philo(&arg);

	if (pthread_mutex_init(&(philo[1].mutex), NULL) != 0)
	{
		fprintf(stderr, "Error: Failed to initialize mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&(philo[2].mutex), NULL) != 0)
	{
		fprintf(stderr, "Error: Failed to initialize mutex\n");
		return (1);
	}

	pthread_create(&(philo[1].philo_id), NULL, do_action, &(philo[1]));
	pthread_create(&(philo[1].monitor_id), NULL, monitor, &(philo[1]));
	pthread_create(&(philo[2].philo_id), NULL, do_action, &(philo[2]));
	pthread_create(&(philo[2].monitor_id), NULL, monitor, &(philo[2]));
	pthread_join(philo[1].monitor_id, (void *)(&is_someone_died));
	pthread_join(philo[2].monitor_id, (void *)(&is_someone_died));
	if (is_someone_died)
	{
		if (pthread_mutex_destroy(&(philo[1].mutex)) != 0)
		{
			fprintf(stderr, "Error: Failed to destroy mutex\n");
			pthread_exit(NULL);
		}
		if (pthread_mutex_destroy(&(philo[2].mutex)) != 0)
		{
			fprintf(stderr, "Error: Failed to destroy mutex\n");
			pthread_exit(NULL);
		}
		pthread_detach(philo[1].philo_id);
		pthread_detach(philo[2].philo_id);
		return (0);
	}
	pthread_join(philo[1].philo_id, NULL);
	pthread_join(philo[2].philo_id, NULL);
	if (pthread_mutex_destroy(&(philo[1].mutex)) != 0)
	{
		fprintf(stderr, "Error: Failed to destroy mutex\n");
		pthread_exit(NULL);
	}
	if (pthread_mutex_destroy(&(philo[2].mutex)) != 0)
	{
		fprintf(stderr, "Error: Failed to destroy mutex\n");
		pthread_exit(NULL);
	}

	return (0);
}
