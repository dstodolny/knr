#include <stdio.h>

void squeeze(char s[], char t[]);
int include(char s[], int c);

void
squeeze(char s[], char t[])
{
    int i, j, k;

    for (i = j = 0; s[i] != '\0'; i++) {
        if (!include(t, s[i]))
            s[j++] = s[i];
    }
    s[j] = '\0';
}

int
include(char s[], int c)
{
    int i, r;
    r = 0;
    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == c)
            r = 1;
    return r;
}

int
main()
{
    char s[] = "aaiat weoeeerfksfaeaf";
    char t[] = "aef";

    squeeze(s, t);
    printf("%s\n", s);
}
