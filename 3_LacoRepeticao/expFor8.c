#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){

    for(int i = 0 ; i < 256 ; i++){
        printf("\t%d - %c\n", i, i);
    }

    system("PAUSE");
    return 0;
}