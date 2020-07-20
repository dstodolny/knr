#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define BUFSIZE 100

int getch(void);
void ungetch(int);

char buf[BUFSIZE];
int bufp = 0;

int getfloat (float *pn)
{
    int c, sign;
    float exp;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');
    if (c == '.') {
        for (c = getch(), exp = 10; isdigit(c); c = getch(), exp *= 10)
            *pn += (c - '0') / exp;
    }
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int main()
{
    int n;
    float array[SIZE];
    for (n = 0; n < SIZE; n++)
        array[n] = 0.0;

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;

    for (n = 0; n < SIZE; n++)
        printf("%f\n", array[n]);
    return 0;
}
