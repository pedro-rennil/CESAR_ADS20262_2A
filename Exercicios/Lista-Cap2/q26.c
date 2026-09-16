#include <stdio.h>
#include <stdlib.h>

int main() {
    float comprimento, largura, preco_metro;

    printf("Digite o comprimento e a largura do terreno em metros: ");
    scanf("%f %f", &comprimento, &largura);

    printf("Digite o preco unitario do metro de arame (R$): ");
    scanf("%f", &preco_metro);

    float perimetro = 2.0f * (comprimento + largura);
    float metros_arame_totais = perimetro * 3.0f; 
    float custo_total = metros_arame_totais * preco_metro;

    printf("Metros totais de arame a comprar: %.2f m\n", metros_arame_totais);
    printf("Custo total do orcamento: R$ %.2f\n", custo_total);

    return 0;
}