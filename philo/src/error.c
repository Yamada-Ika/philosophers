#include "philo.h"

bool	is_err_occured(t_error_kind *err)
{
	return (*err != NO_ERR);
}

void	set_err(t_error_kind *err, t_error_kind kind)
{
	*err = kind;
}

char	*get_err_msg(t_error_kind kind)
{
	static char	*msg[] = {
		"error: Input more philosophers\n",
		"error: Argument number is 4 or 5\n",
		"error: Argument should be positive\n",
		"error: Argument should be numeric\n",
		"error: Failed to memory allocate\n",
		"error: Failed to initialize mutex\n",
		"error: Failed to destroy mutex\n",
		"error: Failed to lock mutex\n",
		"error: Failed to unlock mutex\n",
		"error: Failed to initialize thread attribute\n",
		"error: Failed to add thread attribute\n",
		"error: Failed to create thread\n",
		"error: Failed to detach thread\n",
		"error: Failed to join thread\n",
	};

	return (ft_strdup(msg[kind]));
}

void	print_error(t_error_kind kind)
{
	char	*msg;

	msg = get_err_msg(kind);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}
