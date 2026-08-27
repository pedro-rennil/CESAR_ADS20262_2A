#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Linha 1 (topo): Canto Esq + 2 Horizontais + Canto Dir (4 colunas)
    printf("\xC9\xCD\xCD\xBB\n");
    // Linha 2 (meio): Linha Vertical + 2 Espaços vazios + Linha Vertical (4 colunas)
    printf("\xBA  \xBA\n");
    // Linha 3 (meio): Linha Vertical + 2 Espaços vazios + Linha Vertical (4 colunas)
    printf("\xBA  \xBA\n");
    // Linha 4 (base): Canto Esq Inf + 2 Horizontais + Canto Dir Inf (4 colunas)
    printf("\xC8\xCD\xCD\xBC\n");

    system("PAUSE");
    return 0;
}