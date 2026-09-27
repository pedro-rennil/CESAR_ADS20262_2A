#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    double p, area;

    printf("Digite o comprimento do lado a: ");
    scanf("%lf", &a);
    printf("Digite o comprimento do lado b: ");
    scanf("%lf", &b);
    printf("Digite o comprimento do lado c: ");
    scanf("%lf", &c);
    p = (a + b + c) / 2.0;

    area = sqrt(p * (p - a) * (p - b) * (p - c));

    printf("Semiperimetro (p): %.2f\n", p);
    printf("Area do triangulo: %.2f\n", area);

    return 0;
}