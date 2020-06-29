#include <stdio.h>

int lower(int c);

int
lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int
main()
{
    printf("%c\n", lower('A'));
    printf("%c\n", lower('b'));
    printf("%c\n", lower(':'));
    printf("%c\n", lower('0'));
    return 0;
}
