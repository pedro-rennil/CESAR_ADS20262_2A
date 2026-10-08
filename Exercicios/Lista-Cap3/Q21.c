#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    char secreta = 'a' + (rand() % 26);
    char chute;
    int tentativas = 0;
    printf("=== JOGO DE ADIVINHACAO DE LETRAS ===\n");
    printf("Tente adivinhar a letra secreta entre 'a' e 'z'!\n");
    do {
        printf("Seu palpite: ");
        scanf(" %c", &chute); // Espaco limpa buffer
        tentativas++;
        if (chute < secreta) {
            printf("Dica: A letra secreta vem DEPOIS no alfabeto!\n");
        }
        else if (chute > secreta) {
        printf("Dica: A letra secreta vem ANTES no alfabeto!\n");
        }
    } while (chute != secreta);
    
    printf("\nParabens! Voce acertou a letra '%c' em %d tentativas!\n", secreta, tentativas);
    return 0;
}