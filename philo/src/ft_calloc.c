/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:28:58 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:28:59 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*uc_b;

	i = 0;
	uc_b = (unsigned char *)b;
	while (i < len)
	{
		uc_b[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	mem = malloc(size * count);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, 0, size * count);
	return (mem);
}
