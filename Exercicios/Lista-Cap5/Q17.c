#include <stdio.h>

long fatorialIterativo(int n);
long fatorialRecursivo(int n);

long fatorialIterativo(int n) {
    long resultado = 1;
    int i;
    for (i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

long fatorialRecursivo(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * fatorialRecursivo(n - 1);
}

int main(void) {
    int n;
    long iterativo, recursivo;
    scanf("%d", &n);
    if (n < 0) {
        printf("O numero deve ser nao negativo.\n");
        return 0;
    }
    iterativo = fatorialIterativo(n);
    recursivo = fatorialRecursivo(n);
    printf("Iterativo = %ld\nRecursivo = %ld\n", iterativo, recursivo);
    printf("Resultados %s.\n", iterativo == recursivo ? "coincidem" : "nao coincidem");
    return 0;
}
