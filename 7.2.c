#include <stdio.h>

#define FILLCOL	72

/* print arbitrary input in a sensible way */
int
main()
{
	int c, col;

	col = 1;
	while ((c = getchar()) != EOF) {
		if (col == FILLCOL) {
			col = 1;
			putchar('\n');
		}

		if (c == '\n') {
			col = 1;
			putchar('\n');
		} else if (c != '\t' && (c < 32 || c > 126))
			printf("%o", c);
		else
			putchar(c);
		col++;
	}
	return 0;
}

