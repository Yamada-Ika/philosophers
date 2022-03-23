/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:49:47 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/23 20:51:53 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*create_philo(size_t n)
{
	return ((t_philo *)ft_calloc(n, sizeof(t_philo)));
}

/**
 * @brief Create a structure to pass to each thread
 * 
 */
int	new_philo(t_philo **philo, t_arg *argt, t_error *err)
{
	*philo = create_philo(argt->num_of_philo + 1);
	if (*philo == NULL)
	{
		set_err(err, NO_MEM);
		return (FAILE);
	}
	return (SUCCESS);
}
