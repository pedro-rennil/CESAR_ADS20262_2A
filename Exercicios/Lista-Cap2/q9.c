#include <stdio.h>
#include <stdlib.h>

int main() {
    int n1, n2;

    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &n1, &n2);

    printf("Soma: %d\n", n1 + n2);
    printf("Subtracao: %d\n", n1 - n2);
    printf("Multiplicacao: %d\n", n1 * n2);

    /* TRATAMENTO DE DIVISÃO POR ZERO:
       Para evitar indeterminação matemática, valida-se o divisor antes da operação. */
    if (n2 != 0) {
        printf("Divisao real: %.2f\n", (float)n1 / (float)n2);
    } else {
        printf("Divisao por zero nao eh permitida na matematica.\n");
    }

    return 0;
}