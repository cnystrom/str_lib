
#include <stdlib.h>
#include <string.h>
#include "str_lib.h"

extern size_t strlcpy(char *dst, const char *src, size_t siz);

// Don't forget to free() the pointer...
PUBLIC char *str_null_terminated(char *s, int num)
{
	char *p;

	/* FIX (1.1, 2026): copy all num chars (the malloc is num + 1), not
	 * num - 1, stop at a NUL, and treat a negative num (a failed read()
	 * passed straight in) as 0 instead of overflowing p. */
	if (num < 0)
		num = 0;

	p = (char *) malloc(num + 1);

	if (p != NULL) {
		strncpy(p, s, num);
		p[num] = '\0';
	}

	return (p);
}
