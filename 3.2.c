#include <stdio.h>

void escape(char *s, char *t);

void escape(char *s, char *t)
{
    int i = 0;
    int j = 0;
    while (t[i]) {
        switch (t[i]) {
        case '\t':
            s[j++] = '\\';
            s[j] = 't';
            break;
        case '\n':
            s[j++] = '\\';
            s[j] = 'n';
            break;
        default:
            s[j] = t[i];
        }
        i++;
        j++;
    }
    s[j] = '\0';
}

int main()
{
    char s[20];
    char t[] = "ab\t\t\n\n";
    escape(s, t);
    printf("%s\n", s);
    return 0;
}
