#include "main.h"

extern char **environ;

/**
 * print_path_dir - prints each directory contained in the PATH environment
 * variable
 *
 * Return: void
 */
void print_path_dir(void)
{
	char path[5] = "PATH";
	int i, j, check;

	for (i = 0; environ[i]; i++)
	{
		j = 0, check = 0;
		while (environ[i][j] != '=' && path[j] != '\0')
		{
			if (environ[i][j] != path[j])
			{
				check = 1;
				break;
			}
			j++;

		}
		if (check == 0)
		{
			j++;
			while(environ[i][j])
			{
				if (environ[i][j] == ':')
					putchar('\n');
				else
					putchar(environ[i][j]);
				j++;
			}
			putchar('\n');
			break;
		}
	}

}

/**
 * main - check the function
 *
 * Return: 0
 */
int main(void)
{
	print_path_dir();

	return (0);
}
