#include "main.h"

/**
 * get_error - calls the Error according the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @eval: Error value
 * Return: Error
 */
int GetError(data_shell *datash, int eval)
{
	char *Error;

	switch (eval)
	{
	case -1:
		Error = Error_Env(datash);
		break;
	case 126:
		Error = err_Path_126(datash);
		break;
	case 127:
		Error = Error_Not_Found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			Error = Error_Exit_Shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			Error = Error_Get_Cd(datash);
		break;
	}

	if (Error)
	{
		write(STDERR_FILENO, Error, _strlen(Error));
		free(Error);
	}

	datash->status = eval;
	return (eval);
}
