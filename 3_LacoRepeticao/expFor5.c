#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int num;

    printf("Digite um número inteiro 1 a 10 para tabuada: ");
    scanf("%d", &num);
    
    printf(".:: Tabuada do %d ::.\n", num);
    for(int i = 1; i <= 10 ; i++){
        printf("%2d x %2d = %d\n",num, i, num * i);
    }

    system("PAUSE");
    return 0;
}