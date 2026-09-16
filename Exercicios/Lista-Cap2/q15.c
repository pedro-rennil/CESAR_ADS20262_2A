#include <stdio.h>
#include <stdlib.h>

int main() {
    float p1, p2, p3, p4;

    printf("Digite as quatro notas do aluno (P1 P2 P3 P4): ");
    scanf("%f %f %f %f", &p1, &p2, &p3, &p4);

    float media_simples = (p1 + p2 + p3 + p4) / 4.0f;
    // Pesos: 1 para P1 e P2; 2 para P3 e P4. Soma dos pesos = 6.
    float media_ponderada = (p1 * 1.0f + p2 * 1.0f + p3 * 2.0f + p4 * 2.0f) / 6.0f;

    printf("a) Media Aritmetica Simples: %.2f\n", media_simples);
    printf("b) Media Ponderada: %.2f\n", media_ponderada);

    return 0;
}