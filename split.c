#include "main.h"

/**
 * SwapChar - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *SwapChar(char *input, int bool)
{
	int a;

	if (bool == 0)
	{
		for (a = 0; input[a]; a++)
		{
			if (input[a] == '|')
			{
				if (input[a + 1] != '|')
					input[a] = 16;
				else
					a++;
			}

			if (input[a] == '&')
			{
				if (input[a + 1] != '&')
					input[a] = 12;
				else
					a++;
			}
		}
	}
	else
	{
		for (a = 0; input[a]; a++)
		{
			input[a] = (input[a] == 16 ? '|' : input[a]);
			input[a] = (input[a] == 12 ? '&' : input[a]);
		}
	}
	return (input);
}

/**
 * AddNodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void AddNodes(sep_list **head_s, line_list **head_l, char *input)
{
	int a;
	char *line;

	input = SwapChar(input, 0);

	for (a = 0; input[a]; a++)
	{
		if (input[a] == ';')
			add_sep_node_end(head_s, input[a]);

		if (input[a] == '|' || input[a] == '&')
		{
			add_sep_node_end(head_s, input[a]);
			a++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = SwapChar(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * GoNext - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void GoNext(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int LoopSep;
	sep_list *ls_s;
	line_list *ls_l;

	LoopSep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && LoopSep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				LoopSep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				LoopSep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !LoopSep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * SplitCommands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int SplitCommands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	AddNodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = SplitLine(datash->input);
		loop = ExecLine(datash);
		free(datash->args);

		if (loop == 0)
			break;

		GoNext(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	FreeSepList(&head_s);
	FreeLineList(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * SplitLine - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **SplitLine(char *input)
{
	size_t bsize;
	size_t a;
	char **Tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	Tokens = malloc(sizeof(char *) * (bsize));
	if (Tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	Tokens[0] = token;

	for (a = 1; token != NULL; a++)
	{
		if (a == bsize)
		{
			bsize += TOK_BUFSIZE;
			Tokens = _reallocdp(Tokens, a, sizeof(char *) * bsize);
			if (Tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		Tokens[a] = token;
	}

	return (Tokens);
}
