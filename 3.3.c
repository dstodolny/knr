#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 60

void expand(char *s1, char *s2)
{
    int i, j, c;
    char ranges[10];

    i = 0;
    j = 0;

    while (s1[i] != '\0') {
        if (isalnum(s1[i]) && s1[i+1] == '-' &&
            isalnum(s1[i+2]) && s1[i] <= s1[i+2]) {
            for (c = s1[i]; c <= s1[i+2]; c++) {
                s2[j] = c;
                j++;
            }
            i+=3;
        } else {
            s2[j] = s1[i];
            j++;
            i++;
        }
    }
    s2[j] = '\0';
}

int main()
{
    char buffer[BUFSIZE];

    expand("-a-z0-9 ddd", buffer);
    printf("%s\n", buffer);

    expand("a-zA-Z", buffer);
    printf("%s\n", buffer);

    expand("z-a-z", buffer);
    printf("%s\n", buffer);

    expand("a-b-c", buffer);
    printf("%s\n", buffer);
    return 0;
}
