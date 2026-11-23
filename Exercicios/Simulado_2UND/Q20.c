#include <stdio.h>

typedef struct {
    int hora;
    int minuto;
} Horario;

int duracao(Horario ini, Horario fim);

int duracao(Horario ini, Horario fim) {
    return (fim.hora * 60 + fim.minuto) -
           (ini.hora * 60 + ini.minuto);
}

int main(void) {
    Horario inicio, fim;
    int minutos;

    scanf("%d%d", &inicio.hora, &inicio.minuto);
    scanf("%d%d", &fim.hora, &fim.minuto);
    minutos = duracao(inicio, fim);
    printf("Duracao: %d minutos\n", minutos);
    printf("Formato: %dh%02dmin\n", minutos / 60, minutos % 60);
    return 0;
}
