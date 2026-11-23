#include <stdio.h>

int somaDigitos(int n);

int somaDigitos(int n) {
    if (n < 10) { /* Caso base. */
        return n;
    }
    return n % 10 + somaDigitos(n / 10); /* Passo recursivo. */
}

int main(void) {
    int n;
    scanf("%d", &n);
    if (n < 0) {
        n = -n;
    }
    printf("Soma dos digitos = %d\n", somaDigitos(n));
    return 0;
}
