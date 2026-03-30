#include <stdio.h>
#include <math.h>

int main() {
    int a = 2;
    float a2 = 2.0;
    int b = 3;
    float c = 3.0;
    printf("a %% b: %d\n", a % b);
    printf("a %% c: %f\n", fmod(a, c));
    printf("a2 %% b: %f\n", fmod(a2, b));
    return 0;
}