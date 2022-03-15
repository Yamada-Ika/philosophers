/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:29 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:29:29 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_nomem(t_share *share);
void	set_share(t_share *share, t_arg *argt, t_error *err);
void	set_philo(t_philo *philo, size_t index, t_arg *argt, t_share *share);

static int	set_obj_to_philo(t_philo *philo, t_arg *argt,
	t_share *share, t_error *err)
{
	size_t	i;

	i = 1;
	while (i < argt->num_of_philo + 1)
	{
		set_philo(&philo[i], i, argt, share);
		i++;
	}
	return (init_mutex(philo, err));
}

static int	init_philo(t_philo *philo, t_arg *argt, t_error *err)
{
	t_share	share;

	set_share(&share, argt, err);
	if (is_err_occured(err))
		return (1);
	return (set_obj_to_philo(philo, argt, &share, err));
}

static t_philo	*create_philo(size_t n)
{
	return ((t_philo *)ft_calloc(n, sizeof(t_philo)));
}

/**
 * @brief Create a structure to pass to each thread
 * 
 */
int	make_philo(t_philo **philo, t_arg *argt, t_error *err)
{
	*philo = create_philo(argt->num_of_philo + 1);
	if (*philo == NULL)
	{
		set_err(err, NO_MEM);
		return (1);
	}
	return (init_philo(*philo, argt, err));
}
