#include "main.h"

/**
 * Cd_Dot - changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */
void Cd_Dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	Set_Env("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (_strcmp(".", dir) == 0)
	{
		Set_Env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	Reverse_String(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			Reverse_String(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		Set_Env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		Set_Env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * Cd_To - changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */
void Cd_To(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		GetError(datash, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	Set_Env("OLDPWD", cp_pwd, datash);

	cp_dir = _strdup(dir);
	Set_Env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}

/**
 * Cd_Previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void Cd_Previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _GetEnv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	Set_Env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		Set_Env("PWD", cp_pwd, datash);
	else
		Set_Env("PWD", cp_oldpwd, datash);

	p_pwd = _GetEnv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * Cd_To_Home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void Cd_To_Home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _GetEnv("HOME", datash->_environ);

	if (home == NULL)
	{
		Set_Env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		GetError(datash, 2);
		free(p_pwd);
		return;
	}

	Set_Env("OLDPWD", p_pwd, datash);
	Set_Env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
