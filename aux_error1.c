#include "main.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	stringcopy(error, datash->av[0]);
	stringcat(error, ": ");
	stringcat(error, ver_str);
	stringcat(error, ": ");
	stringcat(error, datash->args[0]);
	stringcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		stringcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		stringcat(error, datash->args[1]);
	}

	stringcat(error, "\n");
	stringcat(error, "\0");
	return (error);
}

/**
 * Error_Get_Cd - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *Error_Get_Cd(data_shell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = AuxiliaryItoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * Error_Not_Found - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *Error_Not_Found(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = AuxiliaryItoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	stringcopy(error, datash->av[0]);
	stringcat(error, ": ");
	stringcat(error, ver_str);
	stringcat(error, ": ");
	stringcat(error, datash->args[0]);
	stringcat(error, ": not found\n");
	stringcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * Error_Exit_Shell - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *Error_Exit_Shell(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = AuxiliaryItoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	stringcopy(error, datash->av[0]);
	stringcat(error, ": ");
	stringcat(error, ver_str);
	stringcat(error, ": ");
	stringcat(error, datash->args[0]);
	stringcat(error, ": Illegal number: ");
	stringcat(error, datash->args[1]);
	stringcat(error, "\n\0");
	free(ver_str);

	return (error);
}
