#include <stdio.h>

#define MAX_CHARS	94
#define HIST_CHR	'*'

int main() {
    int c, i, j;
    int nchars[MAX_CHARS];
    for (i = 0; i < MAX_CHARS; i++)
        nchars[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c >= ' ' && c <= (' ' + MAX_CHARS))
            nchars[c-' ']++;
    }

    for (i = 0; i < MAX_CHARS; i++) {
        if (nchars[i] > 0) {
            printf("%c ", i+' ');
            for (j = 0; j < nchars[i]; j++)
                putchar(HIST_CHR);
            printf("\n");
        }
    }
    return 0;
}
