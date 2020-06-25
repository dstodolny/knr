/* detab - replace tabs in the input with proper numbe rof blanks to
 * space to the next tab stop */

#include <stdio.h>

#define TAB_WIDTH	8

int main() {
    int c, nb, nc;

    nb = 0;
    nc = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            nc = 0;
            putchar(c);
        }
        else if (c == '\t') {
            nb = TAB_WIDTH - nc % TAB_WIDTH;
            while (nb > 0) {
                putchar(' ');
                ++nc;
                --nb;
            }
        }
        else {
            ++nc;
            putchar(c);
        }
    }
    return 0;
}
