#include "shell.h"

/**
 * free_arr2 - frees an array of arrays
 * @arr: array name
 * Return: nil
 */
void free_arr2(char **arr)
{
	int j;

	for (j = 0; arr[j] != NULL; j++)
		;

	for (; j > 0; j--)
		free(arr[j - 1]);

	free(arr);
}

/**
 * my_exit - exits the shell
 * @params: parameters in the command struct
 *
 * Return: an exit value
 */
int my_exit(com_mand params)
{
	char **arr;
	int n = 0;

	printf("allocating space for an arr in exit func\n");
	arr = malloc(sizeof(char*) * 3);
	arr[0] = NULL;
	arr[0] = strdup(params.arr[0]);
	arr[1] = strdup(params.arr[1]);
	arr[2] = NULL;
	char **brr = NULL;
	char *token;
	char *input = malloc(sizeof(char) * BUFSIZE);
	int jh, i;

	jh = read(STDIN_FILENO, input, BUFSIZE);
	if (jh > 0)
	{
		brr = malloc(sizeof(char *) * (5));
		token = my_strtok(input, DELIM_T);
		i = 0;
		while (token != NULL)
		{
			brr[i] = malloc(sizeof(char) * (my_strlen(token) + 1));
			my_strcpy(arr[i], token);
			token = my_strtok(NULL, DELIM_T);
			i++;
		}
		brr[i] = NULL;

		stat = execve(brr[0], brr, env);
		if (stat == -1)
		{
			printf("%s: No such file or directory\n", av[0]);
			free_arr2(brr);
			exit(98);
		}
		free_arr2(brr);
		return (0);
	}
	if (params.arr[2])
	{
		printf("%s: too many arguments\n", arr[0]);
		free_arr2(arr);
		printf("second free\n");
		free_arr2(params.arr);
		exit (7);
	}
	arr[2] = NULL;

	/*
	while (params->arr[n])
	{
		arr[n] = my_strdup(params->arr[n]);
		n++;
	}
	*/
	n = strcmp(arr[0], "exit");
	if (n == 0)
	{
		n = atoi(arr[1]);
		free_arr2(arr);
		free_arr2(params.arr);
		printf("Exiting with %d\n", n);
		exit (n);
	}
	else
	{
		free_arr2(arr);
		printf("wrong call\n");
		return (1);
	}
}

/**
 * my_env - exits the shell
 * @params: parameters in the command struct
 *
 * Return: an exit value
 */
int my_env(com_mand params)
{
	char **arr;
	int n = 0;

	printf("allocating space for an arr in env function\n");
	arr = malloc(sizeof(char*) * 3);
	arr[0] = strdup(params.arr[0]);
	arr[1] = NULL;

	n = strcmp(arr[0], "env");
	if (n == 0)
	{
		for (n = 0; environ[n]; n++)
			printf("Environ[%d]", n);
		free_arr2(arr);
		return (0);
	}
	else
	{
		free_arr2(arr);
		free(params.arr[0]);
		params.arr[0] = malloc(sizeof(char) * 5);
		strcpy(params.arr[0], "exit");
		my_exit(params);
	}

	return (0);
}

/* int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv, char **env) */
int main(void)
{
	com_mand params;
	
	params.arr = malloc(sizeof(char *) * 4);
	if (params.arr == NULL)
		printf("Null allocation to arr**\n");
	params.arr[0] = malloc(sizeof(char) * 5);
	strcpy(params.arr[0], "exit");

	params.arr[1] = malloc(sizeof(char) * 2);
	strcpy(params.arr[1], "3");

	params.arr[2] = malloc(sizeof(char) * 2);
	strcpy(params.arr[2], "7");

	printf("%s %s %s\n", params.arr[0], params.arr[1], params.arr[2]);

	params.arr[3] = NULL;

	printf("calling functions...\n");
	my_exit(params);

	printf("main frees\n");
	free(params.arr[0]);
	free(params.arr);
	return (2);
}
