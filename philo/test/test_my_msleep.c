#include "philo.h"

void	test_my_msleep(int argc, char *argv[])
{
	t_philo_info	dummy;
	t_philo_status	status;
	long long		start;

	printf("START: test_my_msleep\n");
	dummy.status = &status;
	for (int i = 0; i < 10; i++)
	{
		start = get_timestamp_in_usec();
		my_msleep(atoi(argv[1]), &dummy);
		printf("%lld\n", get_timestamp_in_usec() - start);
	}
	printf("END: test_my_msleep\n");
}

void	test_my_usleep(int argc, char *argv[])
{
	t_philo_info	dummy;
	t_philo_status	status;
	long long		start;

	printf("START: test_my_usleep\n");
	dummy.status = &status;
	for (int i = 0; i < 100; i++)
	{
		start = get_timestamp_in_usec();
		my_usleep(atoi(argv[1]), &dummy);
		printf("%lld\n", get_timestamp_in_usec() - start);
	}
	printf("END: test_my_usleep\n");
}

void	test_usleep(int argc, char *argv[])
{
	long long		start;

	printf("START: test_usleep\n");
	for (int i = 0; i < 100; i++)
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
	#ifdef MY_MSLEEP
	test_my_msleep(argc, argv);
	#endif
	#ifdef MY_USLEEP
	test_my_usleep(argc, argv);
	#endif
	#ifdef USLEEP
	test_usleep(argc, argv);
	#endif
}
