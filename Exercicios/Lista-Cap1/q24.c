#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Define a largura da primeira coluna em 16 caracteres, alinhados à esquerda (via %-16s)
    printf("%-16s%s\n", "ALUNO(A)", "NOTA");
    printf("%-16s%s\n", "=========", "=====");
    printf("%-16s%s\n", "ALINE", "9.0");
    printf("%-16s%s\n", "MARIO", "DEZ");
    printf("%-16s%s\n", "SERGIO", "4.5");
    printf("%-16s%s\n", "SHIRLEY", "7.0");

    system("PAUSE");
    return 0;
}