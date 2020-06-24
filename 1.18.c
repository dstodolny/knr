#include <stdio.h>
#include "lib/k&r.h"

int is_whitespace(char c);
int trim(char line[]);

int is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

int trim(char line[]) {
    int i;

    for (i = 0; line[i] != '\n'; i++);

    while (is_whitespace(line[i])) {
        i--;
    }
    line[++i] = '\n';
    line[++i] = '\0';
    return i;
}

int main() {
    int len;
    char line[MAXLINE];

    while ((_getline(line, MAXLINE)) > 0)
        if (trim(line) > 1)
            printf("%s", line);
    return 0;
}
