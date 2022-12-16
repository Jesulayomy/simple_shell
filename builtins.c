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
 * Return: 0
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

/**
 * my_set - adds or modifies an environment variable
 * @shell: shell data
 *
 * Return: 0 on completion or -1 otherwise
 */
int my_set(sh_data *shell)
{
	int i, j, k = 0, check, done = 0;
	char **new_env;

	for (i = 0; shell->_environ[i]; i++)
		;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (-1);
	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && shell->arr[1][j] != '\0')
		{
			if (shell->_environ[i][j] != shell->arr[1][j])
				check = 1;
			j++;
		}
		if (check == 0)
		{
			new_env[k] = mod_env(shell);
			k++, done = 1;
			continue;

		}
		new_env[k] = my_strdup(shell->_environ[i]);
		k++;
	}
	if (done == 0)
	{
		new_env[k] = mod_env(shell);
		new_env[k + 1] = NULL;
	}
	else
	{
		new_env[k] = NULL;
	}
	free_arr2(shell->_environ);
	shell->_environ = new_env;
	return (0);
}

/**
 * my_unset - deletes an environment variable
 * @shell: shell data
 *
 * Return: 0 on completion or -1 otherwise
 */
int my_unset(sh_data *shell)
{
	int i, j, k = 0, check, done = 0;
	char **new_env;

	for (i = 0; shell->_environ[i]; i++)
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (-1);

	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && shell->arr[1][j] != '\0')
		{
			if (shell->_environ[i][j] != shell->arr[1][j])
				check = 1;
			j++;
		}
		if (check == 0)
		{
			done = 1;
			continue;
		}
		new_env[k] = my_strdup(shell->_environ[i]);
		k++;
	}

	new_env[k] = NULL;

	if (done == 0)
	{
		perror("Environment variable does not exist\n");
		free_arr2(new_env);
		return (-1);
	}

	free_arr2(shell->_environ);
	shell->_environ = new_env;

	return (0);
}
