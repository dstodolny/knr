#include <stdio.h>

int rightrot(int x, int i);

int
rightrot(int x, int n)
{
    return (int) ((unsigned) x >> n) | (x << (sizeof(int)*8-n));
}

int
main()
{
    int x = 0x96;
    int r = 0x80000025;
    int n = 2;

    printf("%x == %x\n", rightrot(x, 2), r);
    return 0;
}
