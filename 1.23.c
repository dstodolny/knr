#include <stdio.h>
#include "lib/knr.h"

#define IN  1
#define OUT 0

int flip(int state);

int
main()
{
    int c, quoted, chrconst, cmntline, cmntblock;

    quoted = OUT;
    chrconst = OUT;
    cmntline = OUT;
    cmntblock = OUT;

    while ((c = getchar()) != EOF) {
        if (quoted == OUT && chrconst == OUT && c == '/') {
            if ((c = getchar()) == EOF)
                break;
            if (c == '/')
                cmntline = IN;
            else if (c == '*')
                cmntblock = IN;
            else {
                putchar('/');
                putchar(c);
            }
        } else if (quoted == OUT && chrconst == OUT &&
                   cmntblock == IN && c == '*') {
            if ((c = getchar()) == EOF)
                break;
            if (c == '/')
                cmntblock = OUT;
            else {
                putchar('*');
                putchar(c);
            }
        } else if (quoted == OUT && chrconst == OUT &&
                   cmntline == IN && c == '\n') {
            cmntline = OUT;
            putchar(c);
        } else if (c == '"') {
            quoted = flip(quoted);
            putchar(c);
        } else if (c == '\'') {
            chrconst = flip(chrconst);
            putchar(c);
        } else if (cmntline == OUT && cmntblock == OUT)
            putchar(c);
    }

    return 0;
}

int
flip(int state)
{
    if (state == IN)
        state = OUT;
    else
        state = IN;
    return state;
}
