#include <stdio.h>

typedef enum { PENDENTE, PAGO, ENTREGUE } Status;
typedef struct { int codigo; float valor; Status status; } Pedido;

const char *nomeStatus(Status s);

const char *nomeStatus(Status s) {
    return s == PENDENTE ? "Pendente" : s == PAGO ? "Pago" : "Entregue";
}

int main(void) {
    Pedido p[6]; int codigo, novo;
    for (int i = 0; i < 6; i++) {
        scanf("%d%f%d", &p[i].codigo, &p[i].valor, &novo);
        p[i].status = (Status)novo;
    }
    scanf("%d%d", &codigo, &novo);
    for (int i = 0; i < 6; i++) if (p[i].codigo == codigo) p[i].status = (Status)novo;
    for (Status s = PENDENTE; s <= ENTREGUE; s++) {
        int quantidade = 0; float total = 0;
        for (int i = 0; i < 6; i++) if (p[i].status == s) { quantidade++; total += p[i].valor; }
        printf("%s: %d pedido(s), R$ %.2f\n", nomeStatus(s), quantidade, total);
    }
    return 0;
}

