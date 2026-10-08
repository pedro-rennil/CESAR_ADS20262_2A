#include <stdio.h>
int main() {
    int contador = 0;
    for (int i = 1; contador < 100; i++) {
        if (i % 3 == 0) {
            printf("%d\t", i);
            contador++;
            if (contador % 10 == 0) {
                printf("\n"); // Quebra de linha a cada 10 números
            }
    }
    }
    return 0;
}