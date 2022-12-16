#include "shell.h"

/**
 * my_exit - exits the shell
 * @shell: shell data
 *
 * Return: an exit value
 */
int my_exit(sh_data *shell)
{
	int status = 0;

	if (shell->arr[1])
		status = my_atoi(shell->arr[1]);

	free_list(shell->path);
	free_arr2(shell->_environ);
	free_arr2(shell->arr);
	free(shell->line);
	exit(status);
}

/**
 * my_env - prints the environment
 * @shell: shell data
 *
 * Return: an exit value
 */
int my_env(sh_data *shell)
{
	int i, len;

	for (i = 0; shell->_environ[i]; i++)
	{
		len = my_strlen(shell->_environ[i]);
		write(STDOUT_FILENO, shell->_environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}
