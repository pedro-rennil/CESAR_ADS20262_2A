#include <stdio.h>

    int main() {
    printf("DEC\tHEX\tCHAR\n");
    printf("--------------------\n");
    
    for (int code = 32; code <= 126; code++) {
        printf("%3d\t%2X\t %c\n", code, code, code);
    }
    return 0;
}