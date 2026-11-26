
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "str_lib.h"

// Looks like it removes trailing whitespace...
PUBLIC void strclean(char *s)
{
	int len;

	len = strlen(s);

	len--;

	while (isspace(*(s + len))) {
		len--;
	}

	*(s + len + 1) = '\0';
}
