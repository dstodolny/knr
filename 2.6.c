#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

unsigned
setbits(unsigned x, int p, int n, unsigned y)
{
    return (x & ~(~(~0 << n)<<(p+1-n))) |
        (y & ~(~0 << n))<<(p+1-n);
}

int
main()
{
    unsigned x = 0xcc;
    unsigned y = 0x12;
    unsigned r = 0x94;

    printf("%x == %x\n", setbits(x, 6, 4, y), r);
}
