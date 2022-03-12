#include "philo.h"

static bool	is_invalid_arg_num(int argc)
{
	if (argc == 5 || argc == 6)
		return (false);
	return (true);
}

static long long	gen_num(char *s, t_error_kind *err)
{
	long long	num;
	char		*end;

	num = ft_strtoll(s, &end, 10);
	if (num < 0)
	{
		set_err(err, ARG_MINUS);
		return (1);
	}
	if (*end != '\0' || ft_strcmp(s, "+") == 0 || ft_strcmp(s, "-") == 0)
	{
		set_err(err, ARG_NUMERIC);
		return (1);
	}
	return (num);
}

/**
 * @brief コマンドライン引数をチェックし、適切な引数だとt_argに格納する関数。
 * 
 * @param argc プログラム名を含むコマンドライン引数の数
 * @param argv プログラム名を含むコマンドライン引数の値
 * @param argt コマンドライン引数を格納する構造体
 * @param err エラーを格納する変数
 * @return int エラーが発生すると1を返し、それ以外は0
 */
int	validate_arg(int argc, char *argv[], t_arg *argt, t_error_kind *err)
{
	if (is_invalid_arg_num(argc))
	{
		set_err(err, ARG_NUM);
		return (1);
	}
	argt->num_of_philo = gen_num(argv[1], err);
	if (argt->num_of_philo == 0)
	{
		set_err(err, MORE_PHILO);
		return (1);
	}
	argt->time_to_die = gen_num(argv[2], err);
	argt->time_to_eat = gen_num(argv[3], err);
	argt->time_to_sleep = gen_num(argv[4], err);
	if (argc == 6)
	{
		argt->must_eat_times = gen_num(argv[5], err);
		argt->is_set_eat_cnt = true;
	}
	else
		argt->is_set_eat_cnt = false;
	if (is_err_occured(err))
		return (1);
	return (0);
}
