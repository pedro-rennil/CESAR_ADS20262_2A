#include <stdio.h>
#include <stdlib.h>

int main() {
    float horas_normais, horas_extras;

    printf("Digite o acumulado anual de horas normais: ");
    scanf("%f", &horas_normais);

    printf("Digite o acumulado anual de horas extras: ");
    scanf("%f", &horas_extras);

    float salario_bruto = (horas_normais * 10.0f) + (horas_extras * 15.0f);

    float excedente = (salario_bruto > 12000.0f) ? (salario_bruto - 12000.0f) : 0.0f;
    float imposto = excedente * 0.10f;
    float salario_liquido = salario_bruto - imposto;

    printf("\n--- RELATORIO SALARIAL ANUAL ---\n");
    printf("Salario Anual Bruto: R$ %.2f\n", salario_bruto);
    printf("Imposto Progressivo Retido: R$ %.2f\n", imposto);
    printf("Salario Anual Liquido: R$ %.2f\n", salario_liquido);

    return 0;
}