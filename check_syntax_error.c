#include "main.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @p: index
 * Return: repetitions
 */
int repeated_char(char *input, int p)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, p + 1));

	return (p);
}

/**
 * Error_Sep_Op - finds syntax errors
 *
 * @input: input string
 * @p: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int Error_Sep_Op(char *input, int p, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (Error_Sep_Op(input + 1, p + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (p);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (p);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (p);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (p);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (p);
		}
	}

	return (Error_Sep_Op(input + 1, p + 1, *input));
}

/**
 * FirstChar - finds index of the first char
 *
 * @input: input string
 * @p: index
 * Return: 1 if there is an error. 0 in other case.
 */
int FirstChar(char *input, int *p)
{

	for (*p = 0; input[*p]; *p += 1)
	{
		if (input[*p] == ' ' || input[*p] == '\t')
			continue;

		if (input[*p] == ';' || input[*p] == '|' || input[*p] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * Print_Syntax_Error - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @p: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void Print_Syntax_Error(data_shell *datash, char *input, int p, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[p] == ';')
	{
		if (bool == 0)
			msg = (input[p + 1] == ';' ? ";;" : ";");
		else
			msg = (input[p - 1] == ';' ? ";;" : ";");
	}

	if (input[p] == '|')
		msg = (input[p + 1] == '|' ? "||" : "|");

	if (input[p] == '&')
		msg = (input[p + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = AuxiliaryItoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	stringcopy(error, datash->av[0]);
	stringcat(error, ": ");
	stringcat(error, counter);
	stringcat(error, msg2);
	stringcat(error, msg);
	stringcat(error, msg3);
	stringcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * Check_Syntax_Error - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int Check_Syntax_Error(data_shell *datash, char *input)
{
	int begn = 0;
	int f_char = 0;
	int p = 0;

	f_char = FirstChar(input, &begn);
	if (f_char == -1)
	{
		Print_Syntax_Error(datash, input, begn, 0);
		return (1);
	}

	p = Error_Sep_Op(input + begn, 0, *(input + begn));
	if (p != 0)
	{
		Print_Syntax_Error(datash, input, begn + p, 1);
		return (1);
	}

	return (0);
}
