#include <stdio.h>

int main(void) {
    int idade;
    float renda, valor;

    scanf("%d%f%f", &idade, &renda, &valor);
    if (idade >= 18 && idade <= 70 && renda >= 2000.0f) {
        if (valor <= 10.0f * renda) {
            printf("Emprestimo aprovado!\n");
        } else {
            printf("Valor acima do limite permitido.\n");
        }
    } else {
        printf("Emprestimo negado.\n");
    }

    return 0;
}
