#include <stdio.h>

int ehPrimo(int n);

int ehPrimo(int n) {
    if (n < 2) return 0;
    for (int divisor = 2; divisor * divisor <= n; divisor++) {
        if (n % divisor == 0) return 0;
    }
    return 1;
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        if (ehPrimo(i)) printf("%d ", i);
    }
    printf("\n");
    return 0;
}
