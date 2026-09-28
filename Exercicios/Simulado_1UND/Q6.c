#include <stdio.h>
#include <stdlib.h>

int main() {
    int soma = 0;
    for (int i = 1; i <= 10; i++) {
        if (i == 5) continue;
        if (i == 8) break;
        
    }
    printf("Soma final = %d\n", soma);
    system("PAUSE");
    return 0;
}