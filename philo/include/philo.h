#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct timeval	t_time;

// 引数を一時的に格納する構造体
typedef struct s_arg_info
{
	bool	is_invalid_arg;
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
}	t_arg_info;

typedef struct s_philo_status
{
	bool	is_someone_dead;
	bool	can_start;
}	t_philo_status;

// 哲学者の状態
typedef struct s_philo_info
{
	int		index;
	t_philo_status	*status;
	bool	has_fork_on_lefthand;
	bool	has_fork_on_righthand;
	bool	*forks;
	bool	is_even_group;
	bool	is_died;
	int		philo_number;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_to_die;
	long long	last_meal_time;
	pthread_t	philo_id;
	pthread_t	monitor_id;
	pthread_mutex_t	mutex;
}	t_philo_info;

t_philo_info	*init_philo(t_arg_info *argt);
bool		can_init_mutex(t_philo_info *philo);
bool		can_create_thread(t_philo_info *philo);
bool		can_destroy_mutex(t_philo_info *philo);

void		philo_think(t_philo_info *philo);
void		philo_eat(t_philo_info *philo);
void		philo_sleep(t_philo_info *philo);
void		*do_action(void *argp);
void		*monitor(void *argp);

// forks
void		get_fork_on_leftside(t_philo_info *philo);
void		get_fork_on_rightside(t_philo_info *philo);
void		get_forks(t_philo_info *philo);
void		put_forks(t_philo_info *philo);

// utils
int			get_index(int index, int philos_number);
long long	get_timestamp(void);
long long	get_timestamp_in_usec(void);
void		my_usleep(long long usec);
void		my_msleep(long long msec);
bool		is_somephilo_dead(t_philo_info *philo);

#endif
