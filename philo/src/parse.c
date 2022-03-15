/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:39 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:29:39 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_invalid_arg_num(int argc)
{
	if (argc == 5 || argc == 6)
		return (false);
	return (true);
}

static long long	parse_ll(char *s, t_error *err)
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

static int	parse_arg(int argc, char *argv[], t_arg *argt, t_error *err)
{
	argt->num_of_philo = parse_ll(argv[1], err);
	if (argt->num_of_philo == 0)
	{
		set_err(err, MORE_PHILO);
		return (1);
	}
	argt->time_to_die = parse_ll(argv[2], err);
	argt->time_to_eat = parse_ll(argv[3], err);
	argt->time_to_sleep = parse_ll(argv[4], err);
	if (argc == 6)
	{
		argt->must_eat_times = (size_t)parse_ll(argv[5], err);
		argt->is_set_eat_cnt = true;
	}
	else
		argt->is_set_eat_cnt = false;
	if (is_err_occured(err))
		return (1);
	return (0);
}

/**
 * @brief Check command line arguments and get their values
 * 
 */
int	parse(int argc, char *argv[], t_arg *argt, t_error *err)
{
	if (is_invalid_arg_num(argc))
	{
		set_err(err, ARG_NUM);
		return (1);
	}
	return (parse_arg(argc, argv, argt, err));
}
