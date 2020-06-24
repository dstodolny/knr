#include <stdio.h>
#include "lib/k&r.h"

void reverse(char line[]);

int main() {
    char line[MAXLINE];

    while ((_getline(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
    }
    return 0;
}

void reverse(char s[]) {
    int i, j, c;

    for (j = 0; s[j] != '\0'; j++);
    j--;
    if (s[j] == '\n')
        j--;

    for (i = 0; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
