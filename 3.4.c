#include <stdio.h>
#include <string.h>
#include <limits.h>

int abs(int x)
{
    if (x < 0)
        return -x;
    else
        return x;
}


void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/*
  The original version of itoa doesn't work for INT_MIN because negating
  INT_MIN results in INT_MIN.
*/
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char buf[36];
    itoa(INT_MIN, buf);
    printf("%s\n", buf);
    return 0;
}
