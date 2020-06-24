#include <stdio.h>
#include "lib/k&r.h"

#define LONGLINE 80

int main() {
    int len;
    char line[MAXLINE];

    while ((len = _getline(line, MAXLINE)) > 0)
        if (len > LONGLINE)
            printf("%s", line);

    return 0;
}
