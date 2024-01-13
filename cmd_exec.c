#include "main.h"

/**
 * IsCdir - checks ":" if is in the current directory.
 * @pth: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the pth is searchable in the cd, 0 otherwise.
 */
int IsCdir(char *pth, int *i)
{
	if (pth[*i] == ':')
		return (1);

	while (pth[*i] != ':' && pth[*i])
	{
		*i += 1;
	}

	if (pth[*i])
		*i += 1;

	return (0);
}

/**
 * _Whch - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_Whch(char *cmd, char **_environ)
{
	char *pth, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	pth = _GetEnv("PATH", _environ);
	if (pth)
	{
		ptr_path = _strdup(pth);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (IsCdir(pth, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			stringcopy(dir, token_path);
			stringcat(dir, "/");
			stringcat(dir, cmd);
			stringcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * IsExecutable - determines if is an executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int IsExecutable(data_shell *datash)
{
	struct stat st;
	int i;
	char *inp;

	inp = datash->args[0];
	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == '.')
		{
			if (inp[i + 1] == '.')
				return (0);
			if (inp[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (inp[i] == '/' && i != 0)
		{
			if (inp[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(inp + i, &st) == 0)
	{
		return (i);
	}
	GetError(datash, 127);
	return (-1);
}

/**
 * Check_Err_Cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */
int Check_Err_Cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		GetError(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			GetError(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			GetError(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * Cmd_Exec - executes command lines
 *
 * @datash: data relevant (args and inp)
 * Return: 1 on success.
 */
int Cmd_Exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = IsExecutable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _Whch(datash->args[0], datash->_environ);
		if (Check_Err_Cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _Whch(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
