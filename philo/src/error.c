#include "philo.h"

/**
 * @brief エラーが発生したか確認する関数
 * @details この関数が呼ばれるまでにエラーが発生していると、errにNO_ERR以外がセットされている。
 * 
 * @param err エラーを格納する変数
 * @return true エラーが発生している
 * @return false エラーが発生していない
 */
bool	is_err_occured(t_error *err)
{
	return (*err != NO_ERR);
}

/**
 * @brief Set the err object
 * 
 * @param err エラーを格納する変数
 * @param kind エラーの種類
 */
void	set_err(t_error *err, t_error kind)
{
	*err = kind;
}

static char	*get_err_msg(t_error kind)
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

/**
 * @brief 標準エラー出力にエラーメッセージを出力する関数
 * 
 * @param kind エラーの種類
 */
void	print_error(t_error kind)
{
	char	*msg;

	msg = get_err_msg(kind);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}
