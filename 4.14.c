#include <stdio.h>
#define swap(t,x,y) { t _z = y; y = x; x = _z; }

int main()
{
    int x = 4;
    int y = 2;

    swap(int,x,y);
    printf("x: %d\ty: %d\n", x, y);
    return 0;
}
