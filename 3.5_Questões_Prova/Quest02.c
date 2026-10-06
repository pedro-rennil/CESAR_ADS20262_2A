#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char c = '2';
    int i = 3;
    int res = c + i;
    printf("res = %d", res);
    return 0;

    system("PAUSE");
    return 0;
}