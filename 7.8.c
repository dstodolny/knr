#include <stdio.h>
#include <stdlib.h>

void fprint(FILE *);

int
main(int argc, char *argv[])
{
	FILE *fp;
	int pc = 0;
	char *prog = argv[0];

	if (argc == 1) {
		printf("usage: %s [files ...]\n", prog);
		exit(1);
	}

	while (--argc > 0) {
		if ((fp = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: can't open %s\n",
				 prog, *argv);
			exit(1);
		} else {
			pc++;
			printf("File %d: %s\n", pc, *argv);
			fprint(fp);
			fclose(fp);
			printf("\n\n");
		}
	}
	return 0;
}

void
fprint(FILE *fp)
{
	int c;

	while ((c = getc(fp)) != EOF)
		putchar(c);
}
