#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD		100
#define MAXLNUMS	50
#define DEFLIMIT	6

struct tnode {
	char *word;
	int i;
	int lnums[MAXLNUMS];
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
int getch(void);
void ungetch(int);
int isnoise(char *w);

int lnum = 0;

/* print similar variables in groups */
int
main()
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && !isnoise(word))
			root = addtree(root, word);
	treeprint(root);

	return 0;
}


/* isnoise:  return 1 if w is a noise word */
int
isnoise(char *w)
{
	char **p;
	int nkeys;
	char *ckeywords[] = {
		"the", "and"
	};

	nkeys = sizeof ckeywords / sizeof(ckeywords[0]);
	for (p = ckeywords; p < ckeywords + nkeys; p++)
		if (strcmp(*p, w) == 0)
			return 1;
	return 0;
}



/* addtree:  add a node with w limited by limit chars at or below p */
struct tnode *
addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->i = 0;
		p->lnums[p->i++] = lnum;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		if (p->lnums[p->i - 1] != lnum)
			p->lnums[p->i++] = lnum;
	} else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}


/* treprint:  in-order print of tree p */
void
treeprint(struct tnode *p)
{
	int *lnumsp;
	if (p != NULL) {
		treeprint(p->left);
		printf("%-20s", p->word);
		for (lnumsp = p->lnums; lnumsp < p->lnums + p->i; lnumsp++) {
			if (lnumsp != p->lnums)
				printf(" ");
			printf("%d", *lnumsp);
		}
		printf("\n");
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

	while (isspace(c = getch()) && c != '\n')
		;
	if (c == '\n') {
		c = getch();
		lnum++;
	}
		
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

