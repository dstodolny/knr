#include <stdio.h>

#define IN 1
#define OUT 0

int main() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}

/* To test this program we can select a range of cases:

   1. Input: none; Output: 0 0 0
   2. Input: a\n; Output: 1 1 2
   3. Input: ab\n; Output: 1 1 3
   4. Input: a a\n; Output: 1 2 4

   The kinds of input that most likely to cause bugs are edge cases
   like: no input, empty space, single new line character, input with
   range of ascii characters, etc.
*/
