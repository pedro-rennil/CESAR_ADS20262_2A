#include <stdio.h>

int main (){
    int N, cont = 1;
    scanf("%d",&N);
    for (int i = 1; i <=N; i++){
        for (int j = 1; j <= i; j++)
        {
            printf("%d ",cont);
            cont++;
        }
        printf("\n");
    }

    return 0;
}