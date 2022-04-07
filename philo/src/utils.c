/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:30:03 by iyamada           #+#    #+#             */
/*   Updated: 2022/04/07 10:19:12 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_someone_dead(t_philo *p)
{
	bool	res;

	if (mutex_lock(&p->mtxes[STATE], &p->mtxes[ERR], p->err) == FAIL)
		return (true);
	res = *(p->should_end);
	if (mutex_unlock(&p->mtxes[STATE], &p->mtxes[ERR], p->err) == FAIL)
		return (true);
	return (res);
}

int	get_index(t_philo *philo, size_t index)
{
	if (index == 0)
		return (philo->num);
	else if (index == philo->num + 1)
		return (1);
	else
		return (index);
}

int	print_action(t_philo *p, char *action)
{
	if (mutex_lock(&p->mtxes[LOG], &p->mtxes[ERR], p->err) == FAIL)
		return (FAIL);
	if (is_someone_dead(p))
	{
		mutex_unlock(&p->mtxes[LOG], &p->mtxes[ERR], p->err);
		return (FAIL);
	}
	printf("%lld %zu %s\n", get_timestamp(), p->index, action);
	return (mutex_unlock(&p->mtxes[LOG], &p->mtxes[ERR], p->err));
}
