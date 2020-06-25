#include <stdio.h>

#define MAXSTACK 100
#define IN       1
#define OUT      0

int islparen(char c);
int isrparen(char c);
char opposite(char c);
int flip(int state);

int
main()
{
    int c, nc, nl, sq, dq;

    sq = dq = OUT;

    char stack[MAXSTACK];
    int sp = 0;

    for (nc = 0, nl = 0; (c = getchar()) != EOF; nc++) {
        if (sp == MAXSTACK) {
            printf("Error: Too many nested levels\n");
            return -1;
        }

        if (c == '\n') {
            nl++;
            nc = 0;
        } else if ((dq == IN || sq == IN) && c == '\\') {
            c = getchar();
        } else if (c == '"' && sq == OUT) {
            dq = flip(dq);
        } else if (c == '\'' && dq == OUT) {
            sq = flip(sq);
        } else if (islparen(c) && sq == OUT && dq == OUT) {
            stack[sp++] = c;
        } else if (isrparen(c) && sq == OUT && dq == OUT) {
            if (c != opposite(stack[sp-1]))
                printf("Mismatched parenthesis at line: %d, column: %d\n", nl, nc);
            else
                sp--;
        }
    }
    return 0;
}

int
islparen(char c)
{
    return c == '(' || c == '[' || c == '{';
}

int
isrparen(char c)
{
    return c == ')' || c == ']' || c == '}';
}

char
opposite(char c)
{
    switch(c)
    {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    default:
        return -1;
    }
}

int
flip(int state)
{
    if (state == OUT)
        return IN;
    else
        return OUT;
}
