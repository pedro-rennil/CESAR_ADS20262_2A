#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int x = 5;
    // Exemplos de Incremento:
    x = x + 1; /* Adiciona 1 a x */
    printf("x = %d\n", x);
    printf("x = %d\n", ++x);       /* Equivalente (Pré-incremento) */
    printf("x = %d\n", x++);       /* Equivalente (Pós-incremento) */
    printf("x = %d\n", x);
    // Exemplos de Decremento:
    x = x - 1; /* Decrementa 1 de x */
    printf("x = %d\n", x);
    printf("x = %d\n", --x);       /* Equivalente (Pré-decremento) */
    printf("x = %d\n", x--);       /* Equivalente (Pós-decremento) */
    printf("x = %d\n", x);

    system("PAUSE");
    return 0;
}