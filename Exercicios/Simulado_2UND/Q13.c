#include <stdio.h>

int main(void) {
    int vendas[4][3], totalLoja, totalProduto[3] = {0, 0, 0};
    int maiorProduto = 0;

    for (int loja = 0; loja < 4; loja++) {
        for (int produto = 0; produto < 3; produto++) {
            scanf("%d", &vendas[loja][produto]);
            totalProduto[produto] += vendas[loja][produto];
        }
    }
    for (int loja = 0; loja < 4; loja++) {
        totalLoja = 0;
        for (int produto = 0; produto < 3; produto++) {
            totalLoja += vendas[loja][produto];
        }
        printf("Total da loja %d: %d\n", loja + 1, totalLoja);
    }
    for (int produto = 1; produto < 3; produto++) {
        if (totalProduto[produto] > totalProduto[maiorProduto]) {
            maiorProduto = produto;
        }
    }
    printf("Produto com mais vendas: %d (%d unidades)\n",
           maiorProduto + 1, totalProduto[maiorProduto]);
    return 0;
}
