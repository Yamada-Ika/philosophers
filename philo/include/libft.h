/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:59:07 by iyamada           #+#    #+#             */
/*   Updated: 2022/03/21 19:00:01 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

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

#endif
