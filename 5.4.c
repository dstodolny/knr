/*
 * Exercise 5-4.  Write the function strend(s,t), which return 1
 * if the string t occurs at the end of the string s, and zero
 * otherwise.
 */

#include <stdio.h>
#include <assert.h>

int strend(char *, char *);

/* Return 1 if t occurs at the end of s. Otherwise return 0. */
int
strend(char *s, char *t)
{
	while (*s && *s != *t)
		s++;
	while (*s++ == *t++) {
		if (*s == '\0' && *t == '\0')
			return 1;
	}

	return 0;
}

/* Test strend function */
int main()
{
	char a[] = "abcdef";
	char b[] = "def";
	char c[] = "de";
	char d[] = "deg";
	char e[] = "ghj";
	char f[] = "123412341234";
	char g[] = "abcdef";

	assert(strend(a, b));
	assert(!strend(a, c));
	assert(!strend(a, d));
	assert(!strend(a, e));
	assert(!strend(a, f));
	assert(strend(a, g));

	return 0;
}
