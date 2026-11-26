/* test_str_lib.c - exercises str_lib (2026). Run with `make test`. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_lib.h"
#include "str_lib_version.h"

static int n_pass, n_fail;
#define CHECK(c) do { if (c) { n_pass++; printf("  ok   %s\n", #c); } \
	else { n_fail++; printf("  FAIL %s  (%s:%d)\n", #c, __FILE__, __LINE__); } } while (0)
#define DONE(name) do { printf("%s: %d passed, %d failed\n", name, n_pass, n_fail); \
	return n_fail ? 1 : 0; } while (0)

int main(void)
{
	char buf[8];
	char s[32];
	char *p;

	printf("str_lib %s (%s)\n", STR_LIB_VERSION, STR_LIB_ORIGIN);

	CHECK(str_len("") == 0);
	CHECK(str_len("hello") == 5);

	strcpy(s, "trailing   \t\n");
	strclean(s);
	CHECK(strcmp(s, "trailing") == 0);
	strcpy(s, "  keep leading");
	strclean(s);
	CHECK(strcmp(s, "  keep leading") == 0);

	/* strlcpy: returns strlen(src), always NUL terminates */
	CHECK(strlcpy(buf, "abc", sizeof(buf)) == 3 && strcmp(buf, "abc") == 0);
	CHECK(strlcpy(buf, "abcdefghij", sizeof(buf)) == 10);
	CHECK(strcmp(buf, "abcdefg") == 0);
	CHECK(strlcpy(buf, "xyz", 0) == 3 && strcmp(buf, "abcdefg") == 0);

	/* strlcat: returns the length it tried to create */
	strlcpy(buf, "abc", sizeof(buf));
	CHECK(strlcat(buf, "de", sizeof(buf)) == 5 && strcmp(buf, "abcde") == 0);
	CHECK(strlcat(buf, "fghij", sizeof(buf)) == 10);
	CHECK(strcmp(buf, "abcdefg") == 0);

	/* str_null_terminated: a NUL-terminated copy of the first num chars.
	 * 1.1 fix: NewIO 0.12 kept only num - 1 chars, read past a buffer
	 * that has no NUL, and overflowed on a negative num. */
	{
		char raw[3] = { 'a', 'b', 'c' };	/* no NUL, as from read() */

		p = str_null_terminated("hello world", 5);
		CHECK(p != NULL && strcmp(p, "hello") == 0);
		free(p);
		p = str_null_terminated(raw, 3);
		CHECK(p != NULL && strcmp(p, "abc") == 0);
		free(p);
		p = str_null_terminated("hi", 5);
		CHECK(p != NULL && strcmp(p, "hi") == 0);
		free(p);
		p = str_null_terminated("x", 0);
		CHECK(p != NULL && strcmp(p, "") == 0);
		free(p);
		p = str_null_terminated("x", -1);	/* read() error */
		CHECK(p != NULL && strcmp(p, "") == 0);
		free(p);
	}

	DONE("str_lib");
}
