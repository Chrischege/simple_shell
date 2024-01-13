#include "main.h"

/**
 * Get_Length - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int Get_Length(int n)
{
	unsigned int n2;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n2 = n * -1;
	}
	else
	{
		n2 = n;
	}
	while (n2 > 9)
	{
		lenght++;
		n2 = n2 / 10;
	}

	return (lenght);
}
/**
 * aux_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *AuxiliaryItoa(int n)
{
	unsigned int n2;
	int lenght = Get_Length(n);
	char *buff;

	buff = malloc(sizeof(char) * (lenght + 1));
	if (buff == 0)
		return (NULL);

	*(buff + lenght) = '\0';

	if (n < 0)
	{
		n2 = n * -1;
		buff[0] = '-';
	}
	else
	{
		n2 = n;
	}

	lenght--;
	do {
		*(buff + lenght) = (n2 % 10) + '0';
		n2 = n2 / 10;
		lenght--;
	}
	while (n2 > 0)
		;
	return (buff);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
