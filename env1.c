#include "main.h"

/**
 * Cmp_Env_Name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int Cmp_Env_Name(const char *nenv, const char *name)
{
	int a;

	for (a = 0; nenv[a] != '='; a++)
	{
		if (nenv[a] != name[a])
		{
			return (0);
		}
	}

	return (a + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_GetEnv(const char *name, char **_environ)
{
	char *ptr_env;
	int a, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (a = 0; _environ[a]; a++)
	{
		/* If name and env are equal */
		mov = Cmp_Env_Name(_environ[a], name);
		if (mov)
		{
			ptr_env = _environ[a];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _ENV - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _ENV(data_shell *datash)
{
	int a, b;

	for (a = 0; datash->_environ[a]; a++)
	{

		for (b = 0; datash->_environ[a][b]; b++)
			;

		write(STDOUT_FILENO, datash->_environ[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
