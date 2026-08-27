#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Declaração e inicialização das variáveis de preço
    float precoLapis = 4.88f;
    float precoBorrachas = 234.54f;
    float precoCanetas = 42.04f;
    float precoCadernos = 8.00f;
    float precoFitas = 13.05f;

    // Alinhamento perfeito: rótulos alinhados à esquerda (width 10) e valores alinhados à direita (%12.2f)
    printf("%-10s%12.2f\n", "Lapis", precoLapis);
    printf("%-10s%12.2f\n", "Borrachas", precoBorrachas);
    printf("%-10s%12.2f\n", "Canetas", precoCanetas);
    printf("%-10s%12.2f\n", "Cadernos", precoCadernos);
    printf("%-10s%12.2f\n", "Fitas", precoFitas);

    system("PAUSE");
    return 0;
}