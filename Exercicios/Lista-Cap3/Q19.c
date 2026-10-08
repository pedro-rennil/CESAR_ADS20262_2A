#include <stdio.h>

int main() {
    int n;
    printf("Digite o termo desejado N: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Por favor, digite um inteiro positivo.\n");
    }
    else {
        long long int t1 = 1, t2 = 1, proximo;
        printf("Sequencia ate o termo %d: ", n);
        for (int i = 1; i <= n; i++) {
            if (i == 1 || i == 2) {
                printf("%lld ", (long long int)1);
            }
            else {
                proximo = t1 + t2;
                t1 = t2;
                t2 = proximo;
                printf("%lld ", proximo);
            }
        }
        printf("\nValor do %d-esimo termo: %lld\n", n, (n == 1 || n == 2) ? 1 : t2);
    }
    return 0;
}