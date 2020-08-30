#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define NUMERIC  1
#define DECR     2
#define FOLD     4
#define DIR      8

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
void error(char *);
void readargs(int argc, char *argv[]);
void _substr(const char *s, char *t, int maxstr);

char option = 0;
int pos1 = 0;
int pos2 = 0;

/* sort input lines */
int
main(int argc, char *argv[])
{
	char *lineptr[MAXLINES];
	int nlines;
	int c, rc = 0;

	readargs(argc, argv);
	if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
		if (option & NUMERIC)
			_qsort((void**) lineptr, 0, nlines-1,
			       (int (*) (void *, void *)) numcmp);
		else
			_qsort((void**) lineptr, 0, nlines-1,
			       (int (*) (void *, void*)) charcmp);
		writelines(lineptr, nlines, option & DECR);
	} else {
		printf("input too big to sort\n");
		rc = -1;
	}
	return rc;
}

/* readargs:  read program arguments */
void
readargs(int argc, char *argv[])
{
	int c;

	while ((--argc > 0 && (c = (*++argv)[0]) == '-') || c == '+') {
		if (c == '-' && !isdigit(*(argv[0]+1)))
			while ((c = *++argv[0]))
				switch(c) {
				case 'd':
					option |= DIR;
					break;
				case 'f':
					option |= FOLD;
					break;
				case 'n':
					option |= NUMERIC;
					break;
				case 'r':
					option |= DECR;
					break;

				default:
					printf("sort: illegal option %c\n", c);
					error("Usage: sort -dfnr [+pos1] [-pos2]");
					break;
				}
		else if (c == '-')
			pos2 = atoi(argv[0]+1);
		else if ((pos1 = atoi(argv[0]+1)) < 0)
			error("Usage: sort -dfnr [+pos1] [-pos2]");
	}
	if (argc || pos1 > pos2)
		error("Usage: sort -dfnr [+pos1] [-pos2]");
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
	char str[MAXLEN];

	_substr(s1, str, MAXLEN);
	v1 = atof(str);
	_substr(s2, str, MAXLEN);
	v2 = atof(str);
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
	char a, b;
	int i, j, endpos;
	extern char option;
	extern int pos1, pos2;
	int fold = (option & FOLD) ? 1 : 0;
	int dir = (option & DIR) ? 1 : 0;

	i = j = pos1;
	if (pos2 > 0)
		endpos = pos2;
	else if ((endpos = strlen(s)) > strlen(t))
		endpos = strlen(t);
	do {
		if (dir) {
			while (i < endpos && !isalnum(s[i]) &&
			       s[i] != ' ' && s[i] != '\0')
				i++;
			while (j < endpos && !isalnum(t[j]) &&
			       t[j] != ' ' && t[j] != '\0')
				j++;
		}
		if (i < endpos && j < endpos) {
			a = fold ? tolower(s[i]) : s[i];
			i++;
			b = fold ? tolower(t[j]) : t[j];
			j++;
			if (a == b && a == '\0')
				return 0;
		}
	} while (a == b && i < endpos && j < endpos);
	return a - b;
}


/* _substr:  get a substirng of s and pu in str */
void
_substr(const char *s, char *str, int maxstr)
{
	int i, j, len;
	extern int pos1, pos2;

	len = strlen(s);
	if (pos2 > 0 && len > pos2)
		len = pos2;
	else if (pos2 > 0 && len < pos2)
		error("substr: string too short");
	for (j = 0, i = pos1; i < len; i++, j++)
		str[j] = s[i];
	str[j] = '\0';
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

void
error(char *s)
{
	printf("%s\n", s);
	exit(1);
}
