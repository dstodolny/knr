#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD  100
#define BUFSIZE  1000

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];


unsigned hash(char *);
void error(int, char *);
int getch(void);
void getdef(void);
int getword(char *, int);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void skipblanks(void);
void undef(char *);
void ungetch(int);
void ungets(char *);

int
main()
{
	char w[MAXWORD];
	struct nlist *p;

	while (getword(w, MAXWORD) != EOF)
		if (strcmp(w, "#") == 0)
			getdef();
		else if (!isalpha(w[0]))
			printf("%s", w);
		else if ((p = lookup(w)) == NULL)
			printf("%s", w);
		else
			ungets(p->defn);
	return 0;
}


/* getdef: get definition and install it */
void
getdef(void)
{
	int c, i;
	char def[MAXWORD], dir[MAXWORD], name[MAXWORD];

	skipblanks();
	if (!isalpha(getword(dir, MAXWORD)))
		error(dir[0], "getdef: expecting a directive after #");
	else if (strcmp(dir, "define") == 0) {
		skipblanks();
		if (!isalpha(getword(name, MAXWORD)))
			error(name[0], "getdef: non-alpha - name expected");
		else {
			skipblanks();
			for (i = 0; i < MAXWORD-1; i++)
				if ((def[i] = getch()) == EOF || def[i] == '\n')
					break;
			def[i] = '\0';
			if (i <= 0)
				error('\n', "getdef: incomplete define");
			else
				install(name, def);
		}
	} else if (strcmp(dir, "undef") == 0) {
		skipblanks();
		if (!isalpha(getword(name, MAXWORD)))
			error(name[0], "getdef: non-alpha in undef");
		else
			undef(name);
	} else
		error(dir[0], "getdef: expecting a directive after #");
}


/* error: print error message and skip the rest of the line */
void
error(int c, char *s)
{
	printf("error: %s\n", s);
	while (c != EOF && c != '\n')
		c = getch();
}

/* skipblanks: skip blank and tab characters */
void
skipblanks(void)
{
	int c;

	while ((c = getch()) == ' ' || c == '\t')
		;
	ungetch(c);
}


/* hash:  form hash value for string s */
unsigned
hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}


/* lookup:  look for s in hashtab */
struct nlist *
lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}


/* install:  put (name, defn) in hashtab */
struct nlist *
install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *) np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}


/* undef:  remove name and definition from the hash table */
void
undef(char *name)
{
	int h;
	struct nlist *np, *prev;

	prev = NULL;
	h = hash(name);
	for (np = hashtab[h]; np != NULL; np = np->next) {
		if (strcmp(name, np->name) == 0)
			break;
		prev = np;
	}

	if (np != NULL) {
		if (prev == NULL)
			hashtab[h] = np->next;
		else
			prev->next = np->next;
		free((void *) np->defn);
		free((void *) np->name);
		free((void *) np);
	}
}


/* getword:  get next word or character from input */
int
getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}


int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;     /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
 
/* ungetch: push a character back onto the input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters \n");
    else
        buf[bufp++] = c;
}


void ungets(char s[])
{
    int i;
    
    i = strlen(s);


    while(i>0)
        ungetch(s[--i]);
}

