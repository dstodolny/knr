#include <stdio.h>
#include <ctype.h>
#include <string.h>

int htoi(const char s[]);
int power(int base, int exp);

int
main()
{
    char s1[] = "0xff";
    char s2[] = "0X0A";
    char s3[] = "0x101";
    char s4[] = "0x0x0x";
    int a, b, c, d;
    a = htoi(s1);
    b = htoi(s2);
    c = htoi(s3);
    d = htoi(s4);
    printf("%d\n%d\n%d\n",  a, b, c);
    printf("%d\n", d);
}

int
htoi(const char s[])
{
    int i, j, v, len;


    if (s[0] == '0' && tolower(s[1]) == 'x')
        i=2;
    else
        i=0;

    len = strlen(s);
    for (j=0; len>i; i++, j++) {
        if (isdigit(s[i])) {
            v += power(16, j) * (s[i] - '0');
        } else if (tolower(s[i]) >= 'a' && tolower(s[i])<='f') {
            v += power(16, j) * ((tolower(s[i])-'a')+10);
        } else
            return 0;
    }
    return v;
}

int
power(int base, int exp)
{
    int i, v;
    v = 1;
    while (exp > 0) {
        v *= base;
        exp--;
    }
    return v;
}
