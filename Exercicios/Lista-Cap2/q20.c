#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float lado_a, lado_b;

    printf("Digite o comprimento dos catetos A e B: ");
    scanf("%f %f", &lado_a, &lado_b);

    float hipotenusa = sqrtf(lado_a * lado_a + lado_b * lado_b);

    printf("Comprimento da Hipotenusa: %.2f\n", hipotenusa);

    return 0;
}