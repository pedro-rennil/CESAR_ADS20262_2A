#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char ch;

    do{
        printf("\nPressione uma tecla: ");
        ch = getch(); /* Aguarda digitação */
        printf("\n%c\n", ch);
    } while (ch != 'q');

    system("PAUSE");
    return 0;
}