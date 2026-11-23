#include <stdio.h>

typedef struct { int horas, minutos, segundos; } Tempo;

Tempo somaTempo(Tempo a, Tempo b);

Tempo somaTempo(Tempo a, Tempo b) {
    Tempo r = {a.horas + b.horas, a.minutos + b.minutos, a.segundos + b.segundos};
    r.minutos += r.segundos / 60; r.segundos %= 60;
    r.horas += r.minutos / 60; r.minutos %= 60;
    return r;
}

int main(void) {
    Tempo a, b, r;
    scanf("%d%d%d%d%d%d", &a.horas, &a.minutos, &a.segundos,
          &b.horas, &b.minutos, &b.segundos);
    r = somaTempo(a, b);
    printf("%02d:%02d:%02d\n", r.horas, r.minutos, r.segundos);
    return 0;
}

