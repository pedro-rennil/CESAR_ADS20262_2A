#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    for(int i = 10; i >= 1 ; i--){
        printf("6 x %2d = %d\n", i, 6 * i);
    }

    system("PAUSE");
    return 0;
}