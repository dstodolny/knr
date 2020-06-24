#include <stdio.h>

#define IN		1
#define OUT		0
#define MAX_WORD        12
#define UNIT_CHAR	'#'

int main() {
    int c, i, j, state, wc;
    int nwords[MAX_WORD];
    for (i = 0; i < MAX_WORD; i++)
        nwords[i] = 0;

    state = OUT;
    wc = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN && wc < MAX_WORD) {
                nwords[wc-1]++;
            }
            state = OUT;
            wc = 0;
        } else if (state == OUT) {
            state = IN;
            ++wc;
        }
        else {
            ++wc;
        }
    }

    for (i = 0; i < MAX_WORD; i++) {
        printf("%2d ", i+1);
        for (j = 1; j <= nwords[i]; j++) {
            printf("%c", UNIT_CHAR);
        }
        printf("\n");
    }
    return 0;

}
