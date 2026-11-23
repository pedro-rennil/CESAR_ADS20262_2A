#include <stdio.h>

float calculaIMC(float peso, float altura);
void classificaIMC(float imc);

float calculaIMC(float peso, float altura) {
    return peso / (altura * altura);
}

void classificaIMC(float imc) {
    if (imc < 18.5f) {
        printf("Abaixo do peso\n");
    } else if (imc < 25.0f) {
        printf("Peso normal\n");
    } else if (imc < 30.0f) {
        printf("Sobrepeso\n");
    } else {
        printf("Obesidade\n");
    }
}

int main(void) {
    float peso, altura, imc;
    scanf("%f%f", &peso, &altura);
    imc = calculaIMC(peso, altura);
    printf("IMC: %.2f\n", imc);
    classificaIMC(imc);
    return 0;
}
