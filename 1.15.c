#include <stdio.h>

int to_celsius(float fahr);

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("fahr celsius\n");
    while (fahr <= upper) {
        printf("%3.0f %6.1f\n", fahr, to_celsius(fahr));
        fahr = fahr + step;
    }
}

int to_celsius(float fahr) {
    return (5.0/9.0) * (fahr-32.0);
}
