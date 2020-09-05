#include <stdio.h>
#include <ctype.h>

#define YES 1
#define NO  0

int getword(char *, int);
int getch(void);
void ungetch(int);

int
main()
{
	return 0;
}

int
getword(char *word, int lim)
{
	int c, d, comment(void);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	} else if (c == '\'' || c == '"') {
		for ( ; --lim > 0; w++)
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c) {
				w++;
				break;
			} else if (*w == EOF)
				break;
	} else if (c == '/') {
		if ((d = getch()) == '*')
			c = comment();
		else
			ungetch(d);
	}
	*w = '\0';
	return c;
}


int comment(void)
{
	int c;
	while ((c = getch()) != EOF)
		if (c == '*') {
			if ((c = getch()) == '/')
				break;
			else
				ungetch(c);
		}
	return c;
}


char buf = 0;

int getch(void)
{
    char c;
    if (buf)
        c = buf;
    else
        c = getchar();
    buf = 0;
    return c;
}

void ungetch(int c)
{
    if (buf != 0)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}


