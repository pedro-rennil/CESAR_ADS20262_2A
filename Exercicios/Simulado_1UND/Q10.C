#include <stdio.h>
#include <stdlib.h>

int main(){

    int total, hora, min, seg;
    printf("Digite uma o numero de segundos que deseja decompor em horas e minutos: ");
    scanf("%d",&total);

    hora = total/3600;
    min = (total % 3600) / 60;
    seg = total % 60;

    printf("\n%d segundos correspondem a: %d hora(s), %d minuto(s) e %d segundo(s).\n",total, hora, min, seg);
    
    return 0;
}