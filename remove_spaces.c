#include "shell.h"

void trimString(char *str)
{
	int i, j;
	int len = strlen(str);

	i = 0;
	while (str[i] == ' ')
	{
		i++;
	}

	if (i > 0)
	{
		j = 0;
		while (i < len)
		{
			str[j] = str[i];
			i++;
			j++;
		}
		str[j] = '\0';
		len = strlen(str);
	}
	i = len - 1;
	while (str[i] == ' ')
	{
		i--;
	}
	str[i + 1] = '\0';
}
