#include <stdio.h>

long fibonacci(int n);

long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
    int quantidade, i;
    scanf("%d", &quantidade);
    if (quantidade < 0) {
        printf("A quantidade deve ser nao negativa.\n");
        return 0;
    }
    for (i = 0; i < quantidade; i++) {
        printf("%ld ", fibonacci(i));
    }
    printf("\n");
    /*
     * A versao recursiva recalcula os mesmos termos muitas vezes.
     * Por isso, o numero de chamadas cresce rapidamente para n grande.
     */
    return 0;
}
