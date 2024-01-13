#include "main.h"

/**
 * GetSigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void GetSigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
