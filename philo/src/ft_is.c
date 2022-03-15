/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:29:03 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/15 19:29:04 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isalpha(int c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}
