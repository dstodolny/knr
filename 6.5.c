#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];


unsigned hash(char *);
struct nlist *lookup(char *);
void undef(char *);

int
main()
{
	return 0;
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
