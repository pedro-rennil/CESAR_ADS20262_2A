#include <stdio.h>
#include <stdlib.h>

#define PI 3.141593f

int main() {
    float raio;

    printf("Digite o raio da esfera: ");
    scanf("%f", &raio);

    float area_superficie = 4.0f * PI * raio * raio;
    // Importante: (4.0f / 3.0f) garante divisao real. Escrever (4/3) resultaria em 1 devido ao truncamento inteiro.
    float volume = (4.0f / 3.0f) * PI * raio * raio * raio;

    printf("Area de superficie da esfera: %.4f\n", area_superficie);
    printf("Volume da esfera: %.4f\n", volume);

    return 0;
}