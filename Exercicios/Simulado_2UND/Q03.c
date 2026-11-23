#include <stdio.h>

int main(void) {
    int idade, dia;
    float valor = 40.0f;

    scanf("%d%d", &idade, &dia);
    if (dia == 4 || idade < 12 || idade > 60) {
        valor /= 2.0f;
    }

    printf("Valor do ingresso: R$ %.2f\n", valor);
    return 0;
}
