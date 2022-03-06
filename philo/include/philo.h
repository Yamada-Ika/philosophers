#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define FUNC() printf("%s\n", __func__)

typedef struct timeval	t_time;

typedef enum e_error_kind {
	MORE_PHILO,
	ARG_NUM,
	MEMORY,
	INIT_MTX,
	DESTROY_MTX,
	LOCK_MTX,
	UNLOCK_MTX,
	CREATE_THREAD,
	DETACH_PHILO,
	JOIN_THREAD,
}	t_error_kind;

// 引数を一時的に格納する構造体
typedef struct s_arg
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}	t_arg;

typedef struct s_philo
{
	int				index;
	int				philo_number;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_eat_times;
	int				eat_count;
	int				*full_num;
	long long		last_meal_time;
	bool			can_eat;
	bool			is_full;
	bool			*is_odd_ready;
	bool			*is_even_ready;
	bool			*is_init;
	bool			*is_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*log;
	pthread_mutex_t	*state;
	pthread_mutex_t	*count;
	pthread_t		philo_id;
	pthread_t		monitor_id;
}	t_philo;

// init
int	init_philo(t_philo **philo, t_arg *argt, t_error_kind *error_num);
int	init_mutex(t_philo **philo, t_error_kind *error_num);
int	create_thread(t_philo **philo, t_error_kind *error_num);
int	detach_philo(t_philo **philo, t_error_kind *error_num);
int	wait_monitor(t_philo **philo, t_error_kind *error_num);
int	destroy_mutex(t_philo **philo, t_error_kind *error_num);

void	philo_think(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*do_action(void *argp);
void	*monitor(void *argp);

// forks
void	get_fork_on_leftside(t_philo *philo);
void	get_fork_on_rightside(t_philo *philo);
void	get_forks(t_philo *philo);
void	put_forks(t_philo *philo);
void	put_fork_on_leftside(t_philo *philo);
void	put_fork_on_rightside(t_philo *philo);

// utils
int			get_index(int index, int philos_number);
long long	get_timestamp(void);
// long long	get_timestamp(t_philo *philo);
long long	get_timestamp_in_usec(void);
// long long	get_timestamp_in_usec(t_philo *philo);
void		my_usleep(long long usec, t_philo *philo);
void		my_msleep(long long msec, t_philo *philo);
void		wait_odd_group(t_philo *philo);
void		wait_even_group(t_philo *philo);
// void		print_action(pthread_mutex_t *mutex, int philo_index, char *action);
void		print_action(pthread_mutex_t *mutex, int philo_index, char *action);
void		print_error(char *message);
size_t		ft_strlen(const char *s);

#endif
