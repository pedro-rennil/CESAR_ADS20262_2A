#include <stdio.h>
int main() {
    int a, b;
    printf("Digite os valores de A e B: ");
    scanf("%d %d", &a, &b);
    if (a <= b) {
        for (int i = a; i <= b; i++) printf("%d ", i);
        
    }
    else{
        for (int i = a; i >= b; i--) printf("%d ", i);
    }
    printf("\n");
    return 0;
}