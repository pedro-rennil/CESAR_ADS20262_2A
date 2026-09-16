#include <stdio.h>
#include <stdlib.h>

int main() {
    int dia, mes, ano;

    printf("Digite uma data no formato dd/mm/aaaa: ");
    // Utiliza as barras diretamente na string de controle do scanf
    if (scanf("%d/%d/%d", &dia, &mes, &ano) == 3) {
        printf("Data no formato invertido: %04d/%02d/%02d\n", ano, mes, dia);
    } else {
        printf("Erro na leitura da data.\n");
    }

    return 0;
}