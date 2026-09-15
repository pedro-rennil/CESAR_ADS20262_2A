#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char ch;
    
    printf("Digite uma tecla e aperte ENTER: ");
    ch = getchar(); /* Aguarda buffer de entrada */
    printf("Sucessora ASCII: ");
    putchar(ch + 1);
    putchar('\n');

    system("PAUSE");
    return 0;
}