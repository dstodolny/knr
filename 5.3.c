/*
 * Exercise 5-3.  Write a pointer version of the function strcat
 * that we showed in Chapter 2: strcat(s,t) copies the string t
 * to the end of s.
 */

#include <stdio.h>

void mstrcat(char *, char *);

/* strcat:  concatenate t to end of s; s must be big enough */
void
mstrcat(char *s, char *t)
{
	while (*s)
		s++;
	while ((*s++ = *t++))
		;
}

/* Concatenate "def" to "abc" and print the result. */
int
main()
{
	char s[7] = "abc";
	char t[] = "def";

	mstrcat(s, t);
	printf("%s\n", s);

	return 0;
}
