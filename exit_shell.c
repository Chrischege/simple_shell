#include "main.h"

/**
 * ExitShell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int ExitShell(data_shell *datash)
{
	unsigned int Ustatus;
	int Is_Digit;
	int str_len;
	int big_num;

	if (datash->args[1] != NULL)
	{
		Ustatus = _atoi(datash->args[1]);
		Is_Digit = _IsDigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		big_num = Ustatus > (unsigned int)INT_MAX;
		if (!Is_Digit || str_len > 10 || big_num)
		{
			GetError(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (Ustatus % 256);
	}
	return (0);
}
