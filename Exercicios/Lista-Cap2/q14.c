#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Requer vinculacao da biblioteca matematica (-lm no GCC)

int main() {
    float a, b, c;

    printf("Digite os tres lados do triangulo (a b c): ");
    scanf("%f %f %f", &a, &b, &c);

    float p = (a + b + c) / 2.0f; // Semi-perimetro
    float area = sqrtf(p * (p - a) * (p - b) * (p - c));

    printf("Semi-perimetro (p): %.2f\n", p);
    printf("Area do triangulo (Heron): %.2f\n", area);

    return 0;
}