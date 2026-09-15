#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int i, j;

    for (i = 0, j = i; (i + j) < 100; i++, j++)    {
        printf("%d ", i + j);
    }

    system("PAUSE");
    return 0;
}