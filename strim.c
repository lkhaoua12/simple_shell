#include "shell.h"

char *strtrim(char *str)
{
	char *end;

	while (isspace(*str))
		str++;
	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
		end--;

	*(end + 1) = '\0';

	return (str);
}
