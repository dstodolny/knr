#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
    static int i;
    int j, c;

    if (s[i]) {
        c = s[i];
        j = i++;
        reverse(s);
        s[strlen(s)-1-j] = c;
    }
}

int main()
{
    char s[] = "this is a test";
    reverse(s);
    printf("%s\n", s);
    return 0;
}
