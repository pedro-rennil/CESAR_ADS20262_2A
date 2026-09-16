#include <stdio.h>
#include <stdlib.h>

#define PI 3.141593f

int main() {
    float raio;

    printf("Digite o raio do circulo: ");
    scanf("%f", &raio);

    float area = PI * raio * raio;
    float circunferencia = 2.0f * PI * raio;

    printf("Area do circulo: %.4f\n", area);
    printf("Circunferencia: %.4f\n", circunferencia);

    return 0;
}