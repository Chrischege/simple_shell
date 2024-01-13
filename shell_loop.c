#include "main.h"

/**
 * WithoutComment - deletes comments from the inp
 *
 * @in: inp string
 * Return: inp without comments
 */
char *WithoutComment(char *in)
{
	int a, up_to;

	up_to = 0;
	for (a = 0; in[a]; a++)
	{
		if (in[a] == '#')
		{
			if (a == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[a - 1] == ' ' || in[a - 1] == '\t' || in[a - 1] == ';')
				up_to = a;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, a, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * ShellLoop - Loop of shell
 * @datash: data relevant (av, inp, args)
 *
 * Return: no return.
 */
void ShellLoop(data_shell *datash)
{
	int loop, i_eof;
	char *inp;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		inp = ReadLine(&i_eof);
		if (i_eof != -1)
		{
			inp = WithoutComment(inp);
			if (inp == NULL)
				continue;

			if (Check_Syntax_Error(datash, inp) == 1)
			{
				datash->status = 2;
				free(inp);
				continue;
			}
			inp = RepVar(inp, datash);
			loop = SplitCommands(datash, inp);
			datash->counter += 1;
			free(inp);
		}
		else
		{
			loop = 0;
			free(inp);
		}
	}
}
