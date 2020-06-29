#include <stdio.h>

int binsearch(int x, int v[], int n);

int
binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low+high) / 2;
    while (low <= high && x != v[mid]) {
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid + 1;
        else
            low = mid + 1;
        mid = (low+high) / 2;
    }
    if (x == v[mid])
        return mid;
    else
        return -1;
}

int
main()
{
    int vals[] = {1, 2, 3, 4, 5};

    printf("%d\n", binsearch(6, vals, 5));
    printf("%d\n", binsearch(2, vals, 5));
    return 0;
}
