#include "main.h"

/**
 * Cd_Shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int Cd_Shell(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		Cd_To_Home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		Cd_Previous(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		Cd_Dot(datash);
		return (1);
	}

	Cd_To(datash);

	return (1);
}
