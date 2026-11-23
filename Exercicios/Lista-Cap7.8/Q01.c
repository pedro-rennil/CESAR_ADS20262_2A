#include <stdio.h>

#define TAM 10

int main(void) {
    float notas[TAM], soma = 0.0f, maior, menor, media;
    int acima = 0;

    for (int i = 0; i < TAM; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &notas[i]);
        soma += notas[i];
    }
    maior = menor = notas[0];
    media = soma / TAM;
    for (int i = 0; i < TAM; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        if (notas[i] > media) acima++;
    }
    printf("Media: %.2f\nMaior: %.2f\nMenor: %.2f\nAcima da media: %d\n",
           media, maior, menor, acima);
    return 0;
}

