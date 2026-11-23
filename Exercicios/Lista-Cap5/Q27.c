#include <stdio.h>

float celsiusParaFahrenheit(float celsius);
float celsiusParaKelvin(float celsius);
float fahrenheitParaCelsius(float fahrenheit);
float kelvinParaCelsius(float kelvin);

float celsiusParaFahrenheit(float celsius) {
    return celsius * 9.0f / 5.0f + 32.0f;
}

float celsiusParaKelvin(float celsius) {
    return celsius + 273.15f;
}

float fahrenheitParaCelsius(float fahrenheit) {
    return (fahrenheit - 32.0f) * 5.0f / 9.0f;
}

float kelvinParaCelsius(float kelvin) {
    return kelvin - 273.15f;
}

int main(void) {
    int opcao;
    float temperatura, resultado;
    printf("1 - Celsius para Fahrenheit\n");
    printf("2 - Celsius para Kelvin\n");
    printf("3 - Fahrenheit para Celsius\n");
    printf("4 - Kelvin para Celsius\n");
    scanf("%d", &opcao);
    scanf("%f", &temperatura);
    switch (opcao) {
        case 1: resultado = celsiusParaFahrenheit(temperatura); break;
        case 2: resultado = celsiusParaKelvin(temperatura); break;
        case 3: resultado = fahrenheitParaCelsius(temperatura); break;
        case 4: resultado = kelvinParaCelsius(temperatura); break;
        default:
            printf("Opcao invalida.\n");
            return 0;
    }
    printf("Resultado = %.2f\n", resultado);
    return 0;
}
