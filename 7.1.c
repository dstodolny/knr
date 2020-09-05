#include <stdio.h>
#include <ctype.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	int (*fp)(int c), c;

	printf("%s\n", *argv);
	if (strcmp(*argv, "upper") == 0)
		fp = toupper;
	else
		fp = tolower;
	while ((c = getchar()) != EOF)
		putchar(fp(c));
	return 0;
}

