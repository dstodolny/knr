#include <stdio.h>
#include <sys/file.h>
#include <stdarg.h>
#include <stdlib.h>

#define BUFSIZ 100

void error(char *, ...);
void filecopy(int, int);

/* cat:  concatenate files, version 3 */
int
main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZ];

	if (argc == 1)
		filecopy(0, 1);
	else
		while (--argc > 0) {
			if ((fd = open(*++argv, O_RDONLY)) == -1) {
				error("cat: can't open %s", *argv);
			} else {
				filecopy(fd, 1);
				close(fd);
			}

		}
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", argv[0]);
		exit(2);
	}
	exit(0);
}

/* filecopy:  copy file ifp to file ofp */
void
filecopy(int ifd, int ofd)
{
	int n;
	char buf[BUFSIZ];


	while ((n = read(ifd, buf, BUFSIZ)) > 0)
		if (write(ofd, buf, n) != n)
			error("cat: write error");
}

/* error:  print an error message and die */
void
error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vprintf(fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}
