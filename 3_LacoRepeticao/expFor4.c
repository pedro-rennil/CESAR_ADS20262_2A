#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    for(int i = 3; i <= 100 ; i+=3){
        printf("%3d ", i);
    }

    system("PAUSE");
    return 0;
}