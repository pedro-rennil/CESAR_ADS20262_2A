#include <stdio.h>
#include <stdlib.h>

int main() {
    float lado_quadrado, base, altura;

    printf("Digite o lado L do quadrado: ");
    scanf("%f", &lado_quadrado);

    printf("Digite a base B e a altura H da figura: ");
    scanf("%f %f", &base, &altura);

    float area_quadrado = lado_quadrado * lado_quadrado;
    float area_retangulo = base * altura;
    float area_triangulo = (base * altura) / 2.0f;

    printf("a) Area do Quadrado: %.2f\n", area_quadrado);
    printf("b) Area do Retangulo: %.2f\n", area_retangulo);
    printf("c) Area do Triangulo Retangulo: %.2f\n", area_triangulo);

    return 0;
}