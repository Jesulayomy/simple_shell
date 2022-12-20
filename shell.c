#include "shell.h"

/**
 * get_func - returns functions for builtin commands
 * @arr: the line splitted into command and args
 *
 * Return: the function that prints the builtin command
 */
int (*get_func(char **arr))(sh_data *)
{
	built_in sh[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"setenv", my_set},
		{"unsetenv", my_unset},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	int i = 0;

	if (arr != NULL)
	{
		while (sh[i].func != NULL)
		{
			if (my_strcmp(sh[i].str, arr[0]) == 0)
				return (sh[i].func);
			else
				i++;
		}
	}

	return (NULL);
}

/**
 * loop_shell - runs the shell continously
 * @shell: the shell data
 *
 * Return: void
 */
void loop_shell(sh_data *shell)
{
	char *path;

	for (; ;)
	{
		write(STDIN_FILENO, "($) ", 4);
		fflush(stdout);
		path = check_shell(shell);
		if (!path)
			continue;

		shell->pid = fork();
		if (shell->pid == 0)
		{
			shell->status = execve(path, shell->arr, shell->_environ);
			if (shell->status == -1)
			{
			write(STDERR_FILENO, shell->arr[0], my_strlen(shell->arr[0]));
			write(STDERR_FILENO, ": Permission denied\n", 20);
			free(path);
			shell->status = 13;
			my_exit(shell);
			}
		}
		else
		{
			shell->status = 0;
			wait(NULL);
		}

		free_arr2(shell->arr);
		free(path);
	}
}

/**
 * check_shell - checks the shell commands, paths and builtins
 * @shell: pointer to shell data structure
 *
 * Return: path or NULL
 */
char *check_shell(sh_data *shell)
{
	int (*built_in_func)(sh_data *sh);
	char *path;

	shell->arr = get_commands(shell->line, shell->length);
	if (!shell->arr)
	{
		free(shell->line);
		return (NULL);
	}
	check_alias(shell);
	expand_var(shell);
	built_in_func = get_func(shell->arr);

	if (built_in_func != NULL)
	{
		shell->status = built_in_func(shell);
		free_arr2(shell->arr);
		return (NULL);
	}
	path = search_path(shell->path, shell->arr[0]);

	if (!path)
	{
		write(STDERR_FILENO, shell->arr[0], my_strlen(shell->arr[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		shell->status = 2;
		free_arr2(shell->arr);
		free(path);
		return (NULL);
	}
	return (path);
}

/**
 * expand_var - expands a variable to its corresponding value
 * @shell: pointer to shell structure
 *
 * Return: void
 */
void expand_var(sh_data *shell)
{
	int i, j, k;
	char *str, *value;

	for (i = 0; shell->arr[i]; i++)
	{
		if (my_strcmp(shell->arr[i], "$$") == 0)
		{
			free(shell->arr[i]);
			str = my_itoa(shell->pid);
			shell->arr[i] = my_strdup(str);
			free(str);
		}
		else if (my_strcmp(shell->arr[i], "$?") == 0)
		{
			free(shell->arr[i]);
			str = my_itoa(shell->status);
			shell->arr[i] = my_strdup(str);
			free(str);
		}
		else if (shell->arr[i][0] == '$')
		{
			str = malloc(sizeof(char) * my_strlen(shell->arr[i]));

			for (j = 1, k = 0; shell->arr[i][j]; j++, k++)
				str[k] = shell->arr[i][j];
			str[k] = '\0';

			value = _getenv(shell, str);
			if (value == NULL)
			{
				free(value);
				free(str);
			}
			else
			{
				free(shell->arr[i]);
				free(str);
				shell->arr[i] = my_strdup(value);
				free(value);
			}
		}
	}
}

/**
 * main - main body of the shell
 * @ac: command line argument count
 * @av: pointer to strings of command line arguments
 * @env: environment variables
 *
 * Return: 0 at successful exit
 */
int main(int ac, char *av[], char *env[])
{
	sh_data shell;
	int i;


	shell.line = NULL;
	shell.length = 0;
	shell.pid = getpid();
	shell.status = 0;
	shell.arr = NULL;
	shell.av = av;
	shell.alias = NULL;

	for (i = 0; env[i]; i++)
		;

	shell._environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; env[i]; i++)
		shell._environ[i] = my_strdup(env[i]);
	shell._environ[i] = NULL;

	shell.path = path_to_list(&shell);

	(void) ac;

	loop_shell(&shell);

	return (0);
}
