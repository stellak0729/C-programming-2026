#include <stdio.h>

int main() {
    char a = 'A';
    printf("a %%d: %d\n", a);
    printf("a %%i: %i\n", a);
    printf("a %%c: %c\n", a + 32);
    printf("a %%f: %f\n", (float)a);
    return 0;
}