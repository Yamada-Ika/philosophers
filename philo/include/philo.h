/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:30:15 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/19 02:56:57 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 * @brief define error kind
 * 
 */
typedef enum e_error {
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
 * @brief Structure to temporarily store command line arguments
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
 * @brief Structures accessible by each thread
 * @details Pointer variables are shared by each thread
 */
typedef struct s_philo
{
	size_t		index;
	size_t		num;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	time_to_die;
	size_t		must_eat_times;
	size_t		eat_count;
	long long	last_meal_time;
	t_mutex		*time;
	bool		is_full;
	bool		should_count_eat;
	bool		*is_end;
	t_mutex		*state;
	size_t		*full_num;
	t_mutex		*count;
	t_mutex		*forks;
	t_mutex		*log;
	t_mutex		*mtx_err;
	t_error		*err;
	pthread_t	philo_id;
	pthread_t	monitor_id;
}	t_philo;

// parse.c
int			parse(int argc, char *argv[], t_arg *argt,
				t_error *err);

// make_philo.c
int			make_philo(t_philo **philo, t_arg *argt, t_error *err);

// run_thread.c
int			run_philo_thread(t_philo **philo, t_error *err);
int			run_monitor_thread(t_philo **philo, t_error *err);

// wait_thread.c
int			wait_philo(t_philo **philo, t_error *err);
int			wait_monitor(t_philo **philo, t_error *err);

// mutex.c
int			destroy_mutex(t_philo **philo, t_error *err);
int			init_mutex(t_philo *philo, t_error *err);

// error.c
void		print_error(t_error kind);
bool		is_err_occured(t_error *err);
void		set_err(t_error *err, t_error kind);

// action.c
void		*do_action(void *argp);
void		*monitor(void *argp);
void		set_end_dinner_flag(t_philo *philo);
void		kill_thread(t_philo *philo);

// get_forks.c, get_forks2.c
int			get_forks(t_philo *philo);
int			put_forks(t_philo *philo);

// utils.c
long long	get_timestamp(void);
void		my_msleep(long long msec);
int			get_index(int index, int philo_num);
int			print_action(t_philo *philo, char *action);

// pthread
int			mutex_lock(t_mutex *mtx, t_mutex *mtx_err, t_error *err);
int			mutex_unlock(t_mutex *mtx, t_mutex *mtx_err, t_error *err);

// libft functions
long long	ft_strtoll(const char *str, char **endptr, int base);
int			ft_strcmp(const char*s1, const char *s2);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char *c, int fd);
void		*ft_calloc(size_t count, size_t size);

// test for mock

inline static int mock_pthread_create(pthread_t *arg1, pthread_attr_t *arg2, void *arg3(void *), void *arg4)
{
	srand((unsigned int)time(NULL));

	if (rand() % 3 == 0)
	{
		return (pthread_create(arg1, arg2, arg3, arg4));
	}
	fprintf(stderr, "hooked pthread_create\n");
	return (1);
}

inline static int mock_pthread_join(pthread_t arg1, void *arg2)
{
	srand((unsigned int)time(NULL));

	if (rand() % 3 == 0)
	{
		return (pthread_join(arg1, arg2));
	}
	fprintf(stderr, "hooked pthread_join\n");
	return (1);
}

inline static int mock_pthread_mutex_destroy(pthread_mutex_t *arg1)
{
	srand((unsigned int)time(NULL));

	if (rand() % 3 == 0)
	{
		return (pthread_mutex_destroy(arg1));
	}
	fprintf(stderr, "hooked pthread_mutex_destroy\n");
	return (1);
}

inline static int mock_pthread_mutex_lock(pthread_mutex_t *arg1)
{
	srand((unsigned int)time(NULL));

	if (rand() % 3 == 0)
	{
		return (pthread_mutex_lock(arg1));
	}
	fprintf(stderr, "hooked pthread_mutex_lock\n");
	return (1);
}

inline static int mock_pthread_mutex_unlock(pthread_mutex_t *arg1)
{
	srand((unsigned int)time(NULL));

	if (rand() % 3 == 0)
	{
		return (pthread_mutex_unlock(arg1));
	}
	fprintf(stderr, "hooked pthread_mutex_unlock\n");
	return (1);
}

# define pthread_create(arg1, arg2, arg3, arg4) mock_pthread_create(arg1, arg2, arg3, arg4)
# define pthread_join(arg1, arg2) mock_pthread_join(arg1, arg2)
# define pthread_mutex_destroy(arg1) mock_pthread_mutex_destroy(arg1)
# define pthread_mutex_lock(arg1) mock_pthread_mutex_lock(arg1)
# define pthread_mutex_unlock(arg1) mock_pthread_mutex_unlock(arg1)

#endif
