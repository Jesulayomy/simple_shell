#include "shell.h"

/**
 * get_func - returns functions for builtin commands
 * @arr: the line splitted into commands
 *
 * Return: the function that prints the builtin
 */
/*
int (*get_func(char *arr))(com_mand)
{
	built_in sh = {
		{"exit", my_exit},
		{"env", my_env},
		{"setenv", my_set},
		{"unsetenv", my_unset},
		{"cd", my_cd}
		{NULL, NULL}
	};

	int i = 0, j = 0;

	if (arr != NULL)
	{
		while (sh[i].func != NULL)
		{
			if (strcmp(sh[i].str, arr[0]))
			{
				return (sh[i].func);
			}
			else
			{
				i++;
			}
		}
	}

	return (0);
}
*/

/**
 * loop_shell - runs the shell continously
 *
 */
void loop_shell(char **av, char **env, char **arr, pid_t child, int stat, char *line, size_t len)
{
	for (; ;)
	{
		printf("($) ");
		fflush(stdout);
		child = fork();

		if (child == 0)
		{
			arr = get_commands(line, len);
			stat = execve(arr[0], arr, env);
			if (stat == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
				free_arr2(arr);
				exit(98);
			}
			free_arr2(arr);
		}
		else
		{
			wait(NULL);
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
	char *line = NULL;
	size_t len = 0;
	pid_t child = NULL;
	int stat = 0;
	char **arr = NULL;

	(void) ac;
	loop_shell(av, env, arr, child, stat, line, len);

	return (0);
}
