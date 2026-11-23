#include <stdio.h>
#include "areas.h"

int main(void) {
    float raio, base, altura;
    scanf("%f %f %f", &raio, &base, &altura);
    printf("Area do circulo = %.2f\n", A_CIRC(raio));
    printf("Area do retangulo = %.2f\n", A_RET(base, altura));
    printf("Area do triangulo = %.2f\n", A_TRI(base, altura));
    return 0;
}
