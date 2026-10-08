#include <stdio.h>

int main() {
    int valor;
    printf("Digite o valor do saque em R$: ");
    scanf("%d", &valor);
    int cedulas[] = {100, 50, 20, 10, 5, 2};
    int temp = valor;
    printf("\n--- SAQUE PROCESSADO ---\n");

    for (int i = 0; i < 6; i++) {
        int qtd = 0;

        while (temp >= cedulas[i]) {
            temp -= cedulas[i];
            qtd++;
        }

        if (qtd > 0) {
            printf("Cedulas de R$ %3d: %d\n", cedulas[i], qtd);
        }
    }
    if (temp > 0) printf("Sobro nao sacavel (moedas): R$ %d\n", temp);
    
    return 0;
}