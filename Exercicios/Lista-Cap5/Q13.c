#include <stdio.h>

float soma(float a, float b);
float subtrai(float a, float b);
float multiplica(float a, float b);
float divide(float a, float b);

float soma(float a, float b) { return a + b; }
float subtrai(float a, float b) { return a - b; }
float multiplica(float a, float b) { return a * b; }
float divide(float a, float b) { return a / b; }

int main(void) {
    int opcao;
    float a, b;
    printf("1 - Somar\n2 - Subtrair\n3 - Multiplicar\n4 - Dividir\n");
    scanf("%d", &opcao);
    if (opcao < 1 || opcao > 4) {
        printf("Opcao invalida\n");
        return 0;
    }
    scanf("%f %f", &a, &b);
    if (opcao == 4 && b == 0.0f) {
        printf("Nao e possivel dividir por zero.\n");
        return 0;
    }
    switch (opcao) {
        case 1: printf("Resultado = %.2f\n", soma(a, b)); break;
        case 2: printf("Resultado = %.2f\n", subtrai(a, b)); break;
        case 3: printf("Resultado = %.2f\n", multiplica(a, b)); break;
        case 4: printf("Resultado = %.2f\n", divide(a, b)); break;
    }
    return 0;
}
