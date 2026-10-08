#include <stdio.h>
int main() {
    long int soma = 0;
    for (int i = 1; i <= 100; i++) {
        int quad = i * i;
        soma += quad;
        printf("%3d -> %5d\n", i, quad);
    }
    printf("------------------------\n");
    printf("Soma Total dos Quadrados = %ld\n", soma);
    return 0;
}