#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){

    for(int i = 0 ; i < 6 ; i ++){
        printf("%d ", rand() % 60 + 1);
    }

    system("PAUSE");
    return 0;
}