#include <stdio.h>

#define TAM 10

int main(void) {
    float temperaturas[TAM], soma = 0.0f, media, maior;
    int posicaoMaior = 0, acimaMedia = 0;

    for (int i = 0; i < TAM; i++) {
        scanf("%f", &temperaturas[i]);
        soma += temperaturas[i];
    }
    media = soma / TAM;
    maior = temperaturas[0];
    for (int i = 1; i < TAM; i++) {
        if (temperaturas[i] > maior) {
            maior = temperaturas[i];
            posicaoMaior = i;
        }
    }
    for (int i = 0; i < TAM; i++) {
        if (temperaturas[i] > media) acimaMedia++;
    }

    printf("Media: %.2f\n", media);
    printf("Maior: %.2f (posicao %d)\n", maior, posicaoMaior + 1);
    printf("Acima da media: %d\n", acimaMedia);
    return 0;
}
