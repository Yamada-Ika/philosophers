#include "philo.h"

int	init_philo(t_philo **philo, t_arg *argt, t_error_kind *error_num)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*log;
	pthread_mutex_t	*state;
	pthread_mutex_t	*count;
	int				*full_num;
	bool			*is_odd_ready;
	bool			*is_even_ready;
	bool			*is_init;
	bool			*is_end;
	int	i;

	*philo = (t_philo *)calloc(argt->number_of_philosophers + 1, sizeof(t_philo));
	if (*philo == NULL)
	{
		*error_num = MEMORY;
		return (1);
	}
	forks = (pthread_mutex_t *)calloc(argt->number_of_philosophers + 1, sizeof(pthread_mutex_t));
	log = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
	state = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
	count = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
	full_num = (int *)calloc(1, sizeof(int));
	is_odd_ready = (bool *)calloc(1, sizeof(bool));
	is_even_ready = (bool *)calloc(1, sizeof(bool));
	is_init = (bool *)calloc(1, sizeof(bool));
	is_end = (bool *)calloc(1, sizeof(bool));
	i = 1;
	while (i < argt->number_of_philosophers + 1)
	{
		(*philo)[i].index = i;
		(*philo)[i].forks = forks;
		(*philo)[i].philo_number = argt->number_of_philosophers;
		(*philo)[i].time_to_eat = argt->time_to_eat;
		(*philo)[i].time_to_sleep = argt->time_to_sleep;
		(*philo)[i].time_to_die = argt->time_to_die;
		(*philo)[i].must_eat_times = argt->number_of_times_each_philosopher_must_eat;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_meal_time = get_timestamp();
		(*philo)[i].full_num = full_num;
		(*philo)[i].is_odd_ready = is_odd_ready;
		(*philo)[i].is_even_ready = is_even_ready;
		(*philo)[i].is_init = is_init;
		(*philo)[i].is_end = is_end;
		(*philo)[i].state = state;
		(*philo)[i].log = log;
		(*philo)[i].count = count;
		i++;
	}
	return (0);
}
