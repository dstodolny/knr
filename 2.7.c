#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

unsigned
invert(unsigned x, int p, int n)
{
    return x^(~(~0 << n) << (p+1-n));
}

int
main()
{
    unsigned x = 0x93;
    unsigned r = 0xeb;
    int p = 6;
    int n = 4;

    printf("%x == %x\n", invert(x, p, n), r);
}
