#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strsepesc(char **stringp, const char *delim, char esc, int readonly)
{
	char *p, *token;
	
	if (*stringp == NULL)
		return NULL;
	token = *stringp;
	if (strchr(delim, esc) != NULL)
	{
		*stringp = NULL;
		return token;
	}
	p = token;
	while (**stringp != '\0' && strchr(delim, **stringp) == NULL) 
	{		
		if (**stringp == esc)
		{
			++*stringp;
			if (**stringp == '\0')
				break;
		}
		if (!readonly)
			*p++ = **stringp;			
		++(*stringp);
	}	
	if (**stringp == '\0')
		*stringp = NULL;
	else
		++(*stringp);
	if (!readonly)
		*p = '\0';
	return token;
}

int main()
{
	char s[] = "d;f\\;fs:w\\:\\;;", delim[] = ";:", *tmp = s;
	char *token = strsepesc(&tmp, delim, '\\', 1);
	while (token) {
		printf(">>%s<<%s<<\n", token, tmp);
		token = strsepesc(&tmp, delim, '\\', 1);
		printf("read\n");
		fflush(stdout);
	}
	return 0;
}
