#include "main.h"

/**
 * Copy_Info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *Copy_Info(char *name, char *value)
{
	char *new;
	int LenName, LenValue, Len;

	LenName = _strlen(name);
	LenValue = _strlen(value);
	Len = LenName + LenValue + 2;
	new = malloc(sizeof(char) * (Len));
	stringcopy(new, name);
	stringcat(new, "=");
	stringcat(new, value);
	stringcat(new, "\0");

	return (new);
}

/**
 * Set_Env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void Set_Env(char *name, char *value, data_shell *datash)
{
	int a;
	char *var_env, *name_env;

	for (a = 0; datash->_environ[a]; a++)
	{
		var_env = _strdup(datash->_environ[a]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[a]);
			datash->_environ[a] = Copy_Info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, a, sizeof(char *) * (a + 2));
	datash->_environ[a] = Copy_Info(name, value);
	datash->_environ[a + 1] = NULL;
}

/**
 * _SetEnv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _SetEnv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		GetError(datash, -1);
		return (1);
	}

	Set_Env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _UnsetEnv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _UnsetEnv(data_shell *datash)
{
	char **realloc_env;
	char *var_env, *name_env;
	int a, j, k;

	if (datash->args[1] == NULL)
	{
		GetError(datash, -1);
		return (1);
	}
	k = -1;
	for (a = 0; datash->_environ[a]; a++)
	{
		var_env = _strdup(datash->_environ[a]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = a;
		}
		free(var_env);
	}
	if (k == -1)
	{
		GetError(datash, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (a));
	for (a = j = 0; datash->_environ[a]; a++)
	{
		if (a != k)
		{
			realloc_env[j] = datash->_environ[a];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_env;
	return (1);
}
