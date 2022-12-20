#include "shell.h"

/**
 * reverse_str - reverses a string
 * @string: to be reversed
 * Return: a pointer to the destination
 */
void reverse_str(char *string)
{
	char temp;
	int i, j, k;

	for (i = 0; string[i] != '\0'; i++)
		;

	for (j = 0; j < (i - 1); j++)
	{
		for (k = j + 1; k > 0; k--)
		{
			temp = string[k];
			string[k] = string[k - 1];
			string[k - 1] = temp;
		}
	}
}

/**
 * mod_env - adds or modifies and environment variable
 * @shell: shell data
 *
 * Return: varaible with value
 */
char *mod_env(sh_data *shell)
{
	char *str;
	int len1;
	int len2;

	len1 = my_strlen(shell->arr[1]);
	len2 = my_strlen(shell->arr[2]);

	str = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!str)
		return (NULL);

	my_strcpy(str, shell->arr[1]);
	my_strcat(str, "=");
	my_strcat(str, shell->arr[2]);

	return (str);
}

/**
 * mod_dir - modifies a directory
 * @shell: pointer to shell
 * @dir: directory to set
 * @newdir: new directory
 *
 * Return: void
 */
void mod_dir(sh_data *shell, char *dir, char *newdir)
{
	free_arr2(shell->arr);
	shell->arr = malloc(sizeof(char *) * 4);
	shell->arr[0] = my_strdup("setenv");

	if (my_strcmp(dir, "old") == 0)
		shell->arr[1] = my_strdup("OLDPWD");
	else if (my_strcmp(dir, "new") == 0)
		shell->arr[1] = my_strdup("PWD");

	shell->arr[2] = my_strdup(newdir);
	shell->arr[3] = NULL;

	my_set(shell);
}
