#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* compare two files, printing the first line where they differ */
int
main(int argc, char *argv[])
{
	char s[MAXLINE]; 
	char t[MAXLINE];
	FILE *fp1, *fp2;
	int comp;

	if (argc != 3) {
		printf("usage: cmp file1 file2\n");
		return(-1);
	}

	if ((fp1 = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "%s: can't open %s\n", argv[0], *argv);
		return(-1);
	}

	if ((fp2 = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "%s: can't open %s\n", argv[0], *argv);
		return(-1);
	}

	while((fgets(s, MAXLINE, fp1) != NULL) && (fgets(t, MAXLINE, fp2) != NULL)) {
		if (strcmp(s, t)) {
			printf("%s", s);
			printf("%s", t);
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}

