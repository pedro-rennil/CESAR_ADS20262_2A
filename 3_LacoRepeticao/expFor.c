#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int i;

    for(i = 0 ; i < 20 ; i++){
        printf("%c ", '*');
    }

    system("PAUSE");
    return 0;
}