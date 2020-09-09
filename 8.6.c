#include <stdlib.h>

void *_calloc(unsigned n, unsigned size);

void
*_calloc(unsigned n, unsigned size)
{
	unsigned i, nb;
	char *p, *q;

	nb = n * size;

	if ((p = q = malloc(n*size)) != NULL)
		for (i = 0; i < nb; i++)
			*p++ = 0;
	return q;
}

int
main()
{
	return 0;
}
