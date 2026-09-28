#include <stdio.h>
int main(){

    float valDia = 45.00, bruto, grat, imposto;
    int dias;
    printf("Digite a quantidade de dias trabalhados: ");
    scanf("%d", &dias);
    bruto = valDia*dias;
    grat = bruto + (bruto * 0.05);
    imposto = bruto - (bruto * 0.08);

    printf("salario bruto: %.2f, bonificacao de '5' ficando: %.2f, e com imposto: %.2f ",bruto, grat, imposto );

    return 0;
}