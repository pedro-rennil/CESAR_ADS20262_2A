#include <stdio.h>
#include <stdlib.h>

int main() {
    int numero;

    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);

    int antecessor = numero;
    --antecessor; // Decremento unario reduz 1 unidade

    int sucessor = numero;
    ++sucessor;   // Incremento unario adiciona 1 unidade

    printf("Antecessor: %d\n", antecessor);
    printf("Sucessor: %d\n", sucessor);

    return 0;
}