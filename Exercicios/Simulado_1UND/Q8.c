#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main() {
    const float PI = 3.14159265;
    float R, A = 4, V = 4.0/3.0;
    printf("Digite o valor do raio de uma esfera:\t");
    scanf("%f",&R);
    float area = A * PI * (R*R);
    printf("A area da esfera e: %.3f\n",area);
    V = V * PI * pow (R,3);
    printf("O volume da esfera e: %.3f",V);
    return 0;
}