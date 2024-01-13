#include "main.h"

/**
 * Error_Env - err message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: err message.
 */
char *Error_Env(data_shell *datash)
{
	int len;
	char *err;
	char *ver_str;
	char *msg;

	ver_str = AuxiliaryItoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + _strlen(msg) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}

	stringcopy(err, datash->av[0]);
	stringcat(err, ": ");
	stringcat(err, ver_str);
	stringcat(err, ": ");
	stringcat(err, datash->args[0]);
	stringcat(err, msg);
	stringcat(err, "\0");
	free(ver_str);

	return (err);
}
/**
 * err_Path_126 - err message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The err string.
 */
char *err_Path_126(data_shell *datash)
{
	int len;
	char *ver_str;
	char *err;

	ver_str = AuxiliaryItoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	stringcopy(err, datash->av[0]);
	stringcat(err, ": ");
	stringcat(err, ver_str);
	stringcat(err, ": ");
	stringcat(err, datash->args[0]);
	stringcat(err, ": Permission denied\n");
	stringcat(err, "\0");
	free(ver_str);
	return (err);
}
