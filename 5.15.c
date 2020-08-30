#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMERIC  1
#define DECR     2
#define FOLD     4

#define MAXLINES 5000
#define MAXLEN   1000

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int decr);
void _qsort(void *lineptr[], int left, int right,
	    int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int charcmp(const char *, const char *);
int _getline(char *, int);
char *alloc(int);

static char option = 0;

/* sort input lines */
int
main(int argc, char *argv[])
{
	char *lineptr[MAXLINES];
	int nlines;
	int c, rc = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch(c) {
			case 'n':
				option |= NUMERIC;
				break;
			case 'r':
				option |= DECR;
				break;
			case 'f':
				option |= FOLD;
				break;
			default:
				printf("sort: illegal option %c\n", c);
				argc = 1;
				rc = -1;
				break;
			}
	if (argc)
		printf("Usage: sort -nr \n");
	else
		if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
			if (option & NUMERIC)
				_qsort((void**) lineptr, 0, nlines-1,
				       (int (*) (void *, void *)) numcmp);
			else if (option & FOLD)
				_qsort((void**) lineptr, 0, nlines-1,
				       (int (*) (void *, void *)) charcmp);
			else
				_qsort((void**) lineptr, 0, nlines-1,
				       (int (*) (void *, void*)) strcmp);
			writelines(lineptr, nlines, option & DECR);
		} else {
			printf("input too big to sort\n");
			rc = -1;
		}
	return rc;
}

/* _qsort:  sort v[left]...v[right] into increasing order */
void
_qsort(void *v[], int left, int right,
       int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	_qsort(v, left, last-1, comp);
	_qsort(v, last+1, right, comp);
}

/* numcmp:  compare s1 and s2 numerically */
int
numcmp(const char *s1, const char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* charcmp:  return <0 if s<t, 0 if s==t, >0 if s>t */
int charcmp(const char *s, const char *t)
{
	for ( ; tolower(*s) == tolower(*t); s++, t++)
		if (*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}

void
swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = _getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines:  write output lines */
void
writelines(char *lineptr[], int nlines, int decr)
{
	int i;
	if (decr)
		for (i = nlines-1; i >= 0; i--)
			printf("%s\n", lineptr[i]);
	else
		for (i = 0; i < nlines; i++)
			printf("%s\n", lineptr[i]);
}
