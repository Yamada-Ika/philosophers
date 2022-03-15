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

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;
typedef pthread_attr_t	t_attr;

/**
 * @brief エラーの種類を定義
 * 
 */
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
}	t_error;

/**
 * @brief コマンドライン引数を一時的に格納する構造体
 * 
 */
typedef struct s_arg
{
	size_t			num_of_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	size_t			must_eat_times;
	bool			is_set_eat_cnt;
}	t_arg;

typedef struct s_share
{
	bool	*is_end;
	t_mutex	*forks;
	t_mutex	*log;
	t_mutex	*state;
	t_mutex	*count;
	t_mutex	*time;
	t_mutex	*mtx_err;
	t_error	*err;
	size_t	*full_num;
}	t_share;

/**
 * @brief 各スレッドがアクセスできる構造体
 * @details ポインタ変数は各スレッドで共有。アクセスするためにはmutexをかける。
 */
typedef struct s_philo
{
	size_t		index;
	size_t		philo_number;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	time_to_die;
	size_t		must_eat_times;
	size_t		eat_count;
	long long	last_meal_time;
	bool		is_full;
	bool		should_count_eat;
	bool		*is_end;
	size_t		*full_num;
	t_mutex		*forks;
	t_mutex		*log;
	t_mutex		*state;
	t_mutex		*count;
	t_mutex		*time;
	t_mutex		*mtx_err;
	t_error		*err;
	pthread_t	philo_id;
	pthread_t	monitor_id;
}	t_philo;

// arg
int			parse(int argc, char *argv[], t_arg *argt,
				t_error *err);
int			make_philo(t_philo **philo, t_arg *argt, t_error *err);
int			run_philo_thread(t_philo **philo, t_error *err);
int			run_monitor_thread(t_philo **philo, t_error *err);
int			wait_philo(t_philo **philo, t_error *err);
int			wait_monitor(t_philo **philo, t_error *err);
int			destroy_mutex(t_philo **philo, t_error *err);

// error.c
void		print_error(t_error kind);
bool		is_err_occured(t_error *err);
void		set_err(t_error *err, t_error kind);

// mutex
int			init_mutex(t_philo *philo, t_error *err);

// ft func
long long	ft_strtoll(const char *str, char **endptr, int base);
int			ft_strcmp(const char*s1, const char *s2);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char *c, int fd);
void		*ft_calloc(size_t count, size_t size);

// action
void		*do_action(void *argp);
void		*monitor(void *argp);

// forks
int			get_forks(t_philo *philo);
int			put_forks(t_philo *philo);

// utils
int			get_index(int index, int philo_num);
long long	get_timestamp(void);
void		my_msleep(long long msec);
int			print_action(t_philo *philo, char *action);

// pthread
int			mutex_lock(t_mutex *mtx, t_mutex *mtx_err, t_error *err);
int			mutex_unlock(t_mutex *mtx, t_mutex *mtx_err, t_error *err);

#endif
