#include <stdio.h>

int bitcount(unsigned x);

int
bitcount(unsigned x)
{
    int bits;

    for (bits = 0; x != 0; x &= x-1, bits++);
    return bits;
}

int
main()
{
    unsigned x1 = 0x7f;
    unsigned x2 = 0x5555;

    printf("%d == 7\n", bitcount(x1));
    printf("%d == 8\n", bitcount(x2));
    return 0;
}
