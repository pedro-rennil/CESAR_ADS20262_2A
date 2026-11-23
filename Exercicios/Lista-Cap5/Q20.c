#include <stdio.h>

int ehPrimo(int n);

int ehPrimo(int n) {
    int divisor;
    if (n < 2) {
        return 0;
    }
    for (divisor = 2; divisor * divisor <= n; divisor++) {
        if (n % divisor == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int n, i;
    scanf("%d", &n);
    printf("%d %s primo.\n", n, ehPrimo(n) ? "e" : "nao e");
    printf("Primos de 1 a 50: ");
    for (i = 1; i <= 50; i++) {
        if (ehPrimo(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}
