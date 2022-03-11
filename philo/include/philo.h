#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

# define FUNC() fprintf(stderr, "start : %s\n", __func__)
# define END() fprintf(stderr, "end : %s\n", __func__)

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;
typedef pthread_attr_t	t_attr;

typedef enum e_error_kind {
	NO_ERR = -1,
	MORE_PHILO,
	ARG_NUM,
	ARG_MINUS,
	ARG_NUMERIC,
	NO_MEM,
	INIT_MTX,
	DESTROY_MTX,
	LOCK_MTX,
	UNLOCK_MTX,
	INIT_ATTR,
	ADD_ATTR,
	CREATE_THREAD,
	DETACH_PHILO,
	JOIN_THREAD,
}	t_error_kind;

// 引数を一時的に格納する構造体
typedef struct s_arg
{
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			must_eat_times;
	bool			is_set_eat_cnt;
}	t_arg;

typedef struct s_philo
{
	size_t			index;
	size_t			philo_number;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	size_t			must_eat_times;
	size_t			eat_count;
	long long		last_meal_time;
	bool			can_eat;
	bool			is_full;
	bool			should_count_eat;
	size_t			*full_num;
	bool			*is_ready_thread;
	bool			*is_even_ready;
	bool			*is_init;
	bool			*is_end;
	t_mutex	*forks;
	t_mutex	*log;
	t_mutex	*state;
	t_mutex	*count;
	t_mutex	*time;
	pthread_t		philo_id;
	pthread_t		monitor_id;
}	t_philo;

// arg
int			validate_arg(int argc, char *argv[], t_arg *argt, t_error_kind *error_num);

long long	ft_strtoll(const char *str, char **endptr, int base);
int			ft_strncmp(const char*s1, const char *s2, size_t n);
int			ft_strcmp(const char*s1, const char *s2);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
size_t		ft_strlen_s(const char *s);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char *c, int fd);

// error.c
bool	is_err_occured(t_error_kind *err);
void	set_err(t_error_kind *err, t_error_kind kind);
void	print_error(t_error_kind kind);

// init
int		make_philo(t_philo **philo, t_arg *argt, t_error_kind *error_num);
int		make_mutex(t_philo **philo, t_error_kind *error_num);
int		run_philo_thread(t_philo **philo, t_error_kind *error_num);
int		run_monitor_thread(t_philo **philo, t_error_kind *error_num);
int		wait_monitor(t_philo **philo, t_error_kind *error_num);

// action
void	philo_think(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*do_action(void *argp);
void	*monitor(void *argp);

// forks
void	get_forks(t_philo *philo);
void	put_forks(t_philo *philo);

// utils
int			get_index(int index, int philos_number);
long long	get_timestamp(void);
long long	get_timestamp_in_usec(void);
void		my_usleep(long long usec, t_philo *philo);
void		my_msleep(long long msec, t_philo *philo);
void		print_action(t_mutex *mutex, int philo_index, char *action);

#endif
