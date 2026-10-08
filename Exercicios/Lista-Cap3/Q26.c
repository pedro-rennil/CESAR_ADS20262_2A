#include <stdio.h>

int main() {
    int a, b, soma_primos = 0;
    printf("Digite os limites A e B (A < B): ");
    scanf("%d %d", &a, &b);
    printf("Primos no intervalo [%d, %d]: ", a, b);

    for (int num = a; num <= b; num++) {
        if (num > 1) {
            int e_primo = 1;
            for (int i = 2; i * i <= num; i++) {
                if (num % i == 0) { e_primo = 0; break; }
            }
            if (e_primo) {
                printf("%d ", num);
                soma_primos += num;
            }
        }
    }
    printf("\nSoma Total dos Primos = %d\n", soma_primos);
    return 0;
}