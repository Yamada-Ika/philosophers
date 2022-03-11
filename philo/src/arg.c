#include "philo.h"

// void	debug_arg(t_arg *argt)
// {
// 	fprintf(stderr, "number of philo  : %d\n", argt->num_of_philo);
// 	fprintf(stderr, "time to die      : %d\n", argt->time_to_die);
// 	fprintf(stderr, "time to eat      : %d\n", argt->time_to_eat);
// 	fprintf(stderr, "time to sleep    : %d\n", argt->time_to_sleep);
// 	fprintf(stderr, "must eat times   : %d\n", argt->must_eat_times);
// }

static bool	is_invalid_arg_num(int argc)
{
	if (argc == 5 || argc == 6)
		return (false);
	return (true);
}

static size_t	gen_strtonum(char *s, t_error_kind *err)
{
	long	tmp;
	char	*end;

	tmp = (long)ft_strtoll(s, &end, 10);
	if (tmp < 0)
	{
		set_err(err, ARG_MINUS);
		return (1);
	}
	if (*end != '\0' || ft_strcmp(s, "+") == 0)
	{
		set_err(err, ARG_NUMERIC);
		return (1);
	}
	return ((size_t)tmp);
}

int	validate_arg(int argc, char *argv[], t_arg *argt, t_error_kind *err)
{
	if (is_invalid_arg_num(argc))
	{
		set_err(err, ARG_NUM);
		return (1);
	}
	argt->num_of_philo = gen_strtonum(argv[1], err);
	if (argt->num_of_philo == 0)
	{
		set_err(err, MORE_PHILO);
		return (1);
	}
	argt->time_to_die = gen_strtonum(argv[2], err);
	argt->time_to_eat = gen_strtonum(argv[3], err);
	argt->time_to_sleep = gen_strtonum(argv[4], err);
	if (argc == 6)
	{
		argt->must_eat_times = gen_strtonum(argv[5], err);
		argt->is_set_eat_cnt = true;
	}
	else
		argt->is_set_eat_cnt = false;
	if (is_err_occured(err))
		return (1);
	return (0);
}
