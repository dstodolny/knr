#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD		100
#define DEFLIMIT	6

struct tnode {
	char *word;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int limit);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
int getch(void);
void ungetch(int);
int isckey(char *w);

/* print similar variables in groups */
int
main(int argc, char *argv[])
{
	int limit;
	struct tnode *root;
	char word[MAXWORD];

	limit = DEFLIMIT;
	root = NULL;

	if (argc > 2)
		printf("usage: vars [n]\n");
	else {
		if (argc == 2)
			limit = atoi(*++argv);

		while (getword(word, MAXWORD) != EOF)
			if (isalpha(word[0]) && !isckey(word))
				root = addtree(root, word, limit);
		treeprint(root);
	}
	return 0;
}


/* isckey:  return 1 if w is a C keyword */
int
isckey(char *w)
{
	char **p;
	int nkeys;
	char *ckeywords[] = {
		"auto", "break", "case", "char",
		"const", "continue", "default", "do",
		"int", "long", "register", "return",
		"short", "signed", "sizeof", "static",
		"struct", "switch", "typedef", "union",
		"unsigned", "void", "volatile", "while",
		"double", "else", "enum", "extern",
		"float", "for", "goto", "if" };

	nkeys = sizeof ckeywords / sizeof(ckeywords[0]);
	for (p = ckeywords; p < ckeywords + nkeys; p++)
		if (strcmp(*p, w) == 0)
			return 1;
	return 0;
}



/* addtree:  add a node with w limited by limit chars at or below p */
struct tnode *
addtree(struct tnode *p, char *w, int limit)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strndup(w, limit);
		p->left = p->right = NULL;
	} else if ((cond = strncmp(w, p->word, limit)) < 0)
		p->left = addtree(p->left, w, limit);
	else if (cond > 0)
		p->right = addtree(p->right, w, limit);
	return p;
}


/* treprint:  in-order print of tree p */
void
treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%s\n", p->word);
		treeprint(p->right);
	}
}


/* talloc:  make a tnode */
struct tnode *
talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
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

