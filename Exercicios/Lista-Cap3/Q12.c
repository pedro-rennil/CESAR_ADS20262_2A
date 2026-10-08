#include <stdio.h>
int main() {
    printf("CELSIUS\t\tFAHRENHEIT\tKELVIN\n");
    printf("----------------------------------------\n");
    for (int c = 0; c <= 100; c += 5) {
        float f = (9.0 * c) / 5.0 + 32.0;
        float k = c + 273.15;
        printf("%3d C\t\t%6.2f F\t\t%6.2f K\n", c, f, k);
    }
    return 0;
}