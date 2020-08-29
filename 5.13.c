#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lib/knr.h"

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);

int
main(int argc, char **argv)
{
	int n, nlines, offset;
	char **lp;

	n = 10;

	if (argc > 2) {
		printf("Usage: tail [-n]\n");
		return 1;
	}
	if (argc == 2 && (*++argv)[0] == '-' && isdigit((*argv)[1])) {
		n = atoi(++(*argv));
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		offset = nlines - n;
		if (offset < 0)
			offset = 0;
		for (lp = lineptr + offset; lp < lineptr + nlines; lp++)
			printf("%s\n", *lp);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

/* readlines:  read input lines */
int
readlines(char *lineptr[], int maxlines)
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
