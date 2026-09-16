#include <stdio.h>
#include <stdlib.h>

int main() {
    float celsius;

    printf("Digite a temperatura em graus Celsius: ");
    scanf("%f", &celsius);

    // Formularizacao garantindo divisor de ponto flutuante (9.0 / 5.0)
    float fahrenheit = (celsius * 9.0f / 5.0f) + 32.0f;
    float kelvin = celsius + 273.15f;

    printf("Temperatura em Fahrenheit: %.2f °F\n", fahrenheit);
    printf("Temperatura em Kelvin: %.2f K\n", kelvin);

    return 0;
}