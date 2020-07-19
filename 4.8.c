#include <stdio.h>

int getch(void);
void ungetch(int);

char buf = 0;

int getch(void)
{
    char c;
    if (buf)
        c = buf;
    else
        c = getchar();
    buf = 0;
    return c;
}

void ungetch(int c)
{
    if (buf != 0)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}

int main()
{
    return 0;
}
