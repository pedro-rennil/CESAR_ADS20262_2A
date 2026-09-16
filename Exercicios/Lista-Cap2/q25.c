#include <stdio.h>
#include <stdlib.h>

int main() {
    float salario_base;

    printf("Digite o salario-base do funcionario: ");
    scanf("%f", &salario_base);

    /* JUSTIFICATIVA MATEMÁTICA:
       Gratificação = +5% (+0.05 * salario_base)
       Imposto = -7% (-0.07 * salario_base)
       Salário Líquido = salario_base + (0.05 * salario_base) - (0.07 * salario_base)
                       = salario_base * (1.0 + 0.05 - 0.07) = salario_base * 0.98 */
    float gratificacao = salario_base * 0.05f;
    float imposto = salario_base * 0.07f;
    float salario_liquido = salario_base + gratificacao - imposto;

    printf("Salario-Base: R$ %.2f\n", salario_base);
    printf("Gratificacao (5%%): R$ %.2f\n", gratificacao);
    printf("Imposto Retido (7%%): R$ %.2f\n", imposto);
    printf("Salario Liquido Final: R$ %.2f\n", salario_liquido);

    return 0;
}