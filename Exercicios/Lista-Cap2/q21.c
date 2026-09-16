#include <stdio.h>
#include <stdlib.h>

int main() {
    char caractere;

    printf("Digite um caractere qualquer: ");
    scanf(" %c", &caractere);

    /* EXPLICAÇÃO: Em C, o tipo 'char' é um tipo numérico inteiro pequeno de 1 byte.
       Ao imprimir a variavel com %d, o programa exibe o código numerico equivalente da tabela ASCII. */
    printf("O caractere '%c' corresponde ao codigo ASCII inteiro: %d\n", caractere, (int)caractere);

    return 0;
}