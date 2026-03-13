#include <stdio.h>

int main() {
    char strc[5] = "abcd";
    printf("strc %%c: %c\n", strc);
    printf("strc %%s: %s\n", strc);
    printf("strc %%d: %d\n", strc);
    return 0;
}