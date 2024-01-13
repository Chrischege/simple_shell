#include "main.h"

/**
 * Get_Help - function that retrieves help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
*/
int Get_Help(data_shell *datash)
{

	if (datash->args[1] == 0)
		AuxHelpGeneral();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		AuxHelpSetenv();
	else if (_strcmp(datash->args[1], "env") == 0)
		AuxHelpEnv();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		AuxHelpUnsetenv();
	else if (_strcmp(datash->args[1], "help") == 0)
		AuxHelp();
	else if (_strcmp(datash->args[1], "exit") == 0)
		AuxHelpExit();
	else if (_strcmp(datash->args[1], "cd") == 0)
		AuxHelpCd();
	else if (_strcmp(datash->args[1], "alias") == 0)
		AuxHelpAlias();
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}
