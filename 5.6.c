/* 
 * Exercise 5-6.  Rewrite appropriate programs from earlier
 * chapters and exercises with pointers instead of array indexing.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 100

int mgetline(char *, int);
int matoi(char *);
void mitoa(int, char *);
void mreverse(char *);
int mstrindex(char *, char *);

/* getline:  read a line, return length */
int
mgetline(char *s, int lim)
{
	int c;
	char *t = s;

	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n') {
		*s++ = c;
	}
	*s = '\0';
	return s - t;
}


/* atoi:  convert s to integer */
int
atoi(char *s)
{
	int n, sign;
	
	for ( ; isspace(*s); s++);
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		s++;
	for (n = 0; isdigit(*s); s++)
		n = 10 * n + *s - '0';
	return sign * n;
}

/* mitoa:  convert n to characters in s */
void
mitoa(int n, char *s)
{
	int sign;
	char *t = s;
	if ((sign = n) < 0)
		n = -n;
	do {
		*s++ = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	mreverse(t);
}

/* mreverse:  reverse string s in place */
void
mreverse(char *s)
{
	int c;
	char *t;
	
	t = s;
	while (*s != '\n' && *s != '\0')
		s++;

	while (t < --s) {
		c = *t;
		*t++ = *s;
		*s = c;
	}
}

/* mstrindex:  return index of t in s, -1 if none */
int
mstrindex(char *s, char *t)
{
	char *u, *ps, *pt;
	ps = u = s;
	pt = t;
	
	int i = 0;
	while (*s) {
		ps = s;
		pt = t;
		while (*ps == *pt) {
			ps++;
			pt++;
		}
		if (pt > t && (*pt == '\0'))
			return s - u;
		s++;
	}
	return -1;
}

int
main()
{
	return 0;
}
