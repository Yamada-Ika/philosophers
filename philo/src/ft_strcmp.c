#include "philo.h"

static int	ft_strncmp(const char*s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cu_s1;
	const unsigned char	*cu_s2;

	cu_s1 = (const unsigned char *)s1;
	cu_s2 = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	i = 0;
	while (cu_s1[i] == cu_s2[i] && i < n - 1
		&& !(cu_s1[i] == '\0' && cu_s2[i] == '\0'))
		i++;
	return (cu_s1[i] - cu_s2[i]);
}

static size_t	ft_max(size_t num1, size_t num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

int	ft_strcmp(const char*s1, const char *s2)
{
	size_t	longer_len;

	longer_len = ft_max(ft_strlen(s1), ft_strlen(s2));
	return (ft_strncmp(s1, s2, longer_len));
}
