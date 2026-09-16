#include <stdio.h>
#include <stdlib.h>

int main() {
    int dias_trabalhados;
    const float TAXA_DIARIA = 30.0f;

    printf("Digite o numero de dias uteis trabalhados: ");
    scanf("%d", &dias_trabalhados);

    float salario_bruto = dias_trabalhados * TAXA_DIARIA;
    float imposto_retido = salario_bruto * 0.08f; // 8% de IR
    float salario_liquido = salario_bruto - imposto_retido;

    printf("Salario Bruto: R$ %.2f\n", salario_bruto);
    printf("Desconto IR (8%%): R$ %.2f\n", imposto_retido);
    printf("Salario Liquido a Receber: R$ %.2f\n", salario_liquido);

    return 0;
}