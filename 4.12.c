#include <stdio.h>

void itoa(int n, char s[])
{
    static int i;

    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }
    if (n / 10)
        itoa(n / 10, s);
    s[i++] = n % 10 + '0';
}

int main()
{
    char buf[36];
    itoa(1024, buf);
    printf("%s\n", buf);
    return 0;
}
