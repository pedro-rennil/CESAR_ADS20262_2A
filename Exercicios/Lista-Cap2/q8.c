#include <stdio.h>
#include <stdlib.h>

int main() {
    int numero;

    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);

    int quadrado = numero * numero;
    // Cast explicito ou divisao por literal float (10.0f) impede o truncamento inteiro
    float decima_parte = (float)numero / 10.0f;

    printf("a) Quadrado do numero: %d\n", quadrado);
    printf("b) Decima parte: %.2f\n", decima_parte);

    return 0;
}