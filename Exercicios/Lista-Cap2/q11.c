#include <stdio.h>
#include <stdlib.h>

#define PI 3.141593f

int main() {
    float graus;

    printf("Digite o angulo em graus: ");
    scanf("%f", &graus);

    float radianos = graus * (PI / 180.0f);

    printf("Angulo em Radianos: %.6f rad\n", radianos);

    return 0;
}