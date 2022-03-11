#include "philo.h"

void	ft_putstr_fd(char *c, int fd)
{
	size_t	c_len;
	size_t	prev_write_len;
	char	*tmp_c;

	if (c == NULL)
		return ;
	tmp_c = c;
	c_len = ft_strlen_s(tmp_c);
	prev_write_len = c_len % INT_MAX;
	write(fd, tmp_c, prev_write_len);
	tmp_c += prev_write_len;
	c_len /= INT_MAX;
	while (c_len-- > 0)
	{
		write(fd, tmp_c, INT_MAX);
		tmp_c += INT_MAX;
	}
}
