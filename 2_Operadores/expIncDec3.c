#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int i = 3, n;
    n = i * (i + 1) + (++i);
    printf("\n\t i = %d | n = %d", i, n);
    return 0;
}