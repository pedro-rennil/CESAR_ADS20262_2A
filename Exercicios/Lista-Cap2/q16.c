#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float altura_degrau_cm, altura_total_m;

    printf("Digite a altura de cada degrau (em cm): ");
    scanf("%f", &altura_degrau_cm);
    printf("Digite a altura total a alcancar (em metros): ");
    scanf("%f", &altura_total_m);

    // Compatibilização de unidades: metros para centimetros
    float altura_total_cm = altura_total_m * 100.0f;
    
    // Arredondamento para cima garante cobrir a altura inteira
    int degraus = (int)ceilf(altura_total_cm / altura_degrau_cm);

    printf("Quantidade minima de degraus: %d\n", degraus);

    return 0;
}