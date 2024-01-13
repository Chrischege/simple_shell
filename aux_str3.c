#include "main.h"

/**
 * Reverse_String - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void Reverse_String(char *s)
{
	int cnt = 0, a, b;
	char *str, temp;

	while (cnt >= 0)
	{
		if (s[cnt] == '\0')
			break;
		cnt++;
	}
	str = s;

	for (a = 0; a < (cnt - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			temp = *(str + b);
			*(str + b) = *(str + (b - 1));
			*(str + (b - 1)) = temp;
		}
	}
}
