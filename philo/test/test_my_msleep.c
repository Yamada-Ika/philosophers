#include "philo.h"

typedef struct s_arg_info
{
	int			argc;
	char		*argv[];
}	t_arg_info;

void	*test_my_msleep(void *argp)
{
	t_philo_info	dummy;
	t_philo_status	status;
	long long		start;

	printf("START: test_my_msleep\n");
	dummy.status = &status;
	for (int i = 0; i < atoi(argv[2]); i++)
	{
		start = get_timestamp_in_usec();
		my_msleep(atoi(argv[1]), &dummy);
		printf("%lld\n", get_timestamp_in_usec() - start);
	}
	printf("END: test_my_msleep\n");
}

void	*test_my_usleep(void *argp)
{
	t_philo_info	dummy;
	t_philo_status	status;
	long long		start;

	printf("START: test_my_usleep\n");
	dummy.status = &status;
	for (int i = 0; i < atoi(argv[2]); i++)
	{
		start = get_timestamp_in_usec();
		my_usleep(atoi(argv[1]), &dummy);
		printf("%lld\n", get_timestamp_in_usec() - start);
	}
	printf("END: test_my_usleep\n");
}

void	*test_usleep(void *argp)
{
	long long		start;

	printf("START: test_usleep\n");
	for (int i = 0; i < atoi(argv[2]); i++)
	{
		start = get_timestamp_in_usec();
		usleep(atoi(argv[1]));
		printf("%lld\n", get_timestamp_in_usec() - start);
	}
	printf("END: test_usleep\n");
}

// gcc -DMY_USLEEP=1 test_my_msleep.c ../src/utils.c  -I../include && ./a.out; rm -rf a.out
int	main(int argc, char *argv[])
{
	t_arg_info	argt;
	// pthread_t	thread1;
	// pthread_t	thread2;

	if (argc != 3)
	{
		fprintf(stderr, "Error: Invalid argument!\n");
		fprintf(stderr, "  Usage: %s sleep_time test_number\n", argv[0]);
		return (0);
	}
	printf("sleep time: %s\n", argv[1]);
	printf("test time : %s\n", argv[2]);
	// argt.argc = argc;
	// argt.argv = argv;
	#ifdef MY_MSLEEP
	// pthread_create(&thread1, NULL, test_my_msleep(&argt), NULL);
	// pthread_create(&thread2, NULL, test_my_msleep(&argt), NULL);
	// pthread_create(&thread2, NULL, test_my_msleep(&argt), NULL);
	// test_my_msleep(argc, argv);
	#endif
	#ifdef MY_USLEEP
	test_my_usleep(argc, argv);
	#endif
	#ifdef USLEEP
	test_usleep(argc, argv);
	#endif
}
