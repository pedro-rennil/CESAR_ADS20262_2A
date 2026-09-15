#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int varInt = 2000000000;
    int dez = 10;

    varInt = (varInt * dez) / dez;

    printf("varInt = %d\n\n", varInt);
    

    system("PAUSE");
    return 0;
}