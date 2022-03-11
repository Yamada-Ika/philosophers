#include "philo.h"

static size_t	ft_max(size_t num1, size_t num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

int	ft_strcmp(const char*s1, const char *s2)
{
	size_t	longer_len;

	longer_len = ft_max(ft_strlen_s(s1), ft_strlen_s(s2));
	return (ft_strncmp(s1, s2, longer_len));
}
