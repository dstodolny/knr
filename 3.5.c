#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(int n, char s[], int b)
{
    int i, c, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        c = n % b;
        if (c < 10)
            c += '0';
        else
            c += 'a' - 10;
        s[i++] = c;
    } while ((n /= b) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char buf[40];
    itob(257, buf, 16);
    printf("%s\n", buf);
    return 0;
}
