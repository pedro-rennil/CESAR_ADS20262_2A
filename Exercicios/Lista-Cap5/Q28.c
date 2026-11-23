#include <stdio.h>

float calculaSubtotal(float preco, int quantidade);
float aplicaDesconto(float valor, int opcaoPagamento);
float calculaTroco(float total, float pago);

float calculaSubtotal(float preco, int quantidade) {
    return preco * quantidade;
}

float aplicaDesconto(float valor, int opcaoPagamento) {
    if (opcaoPagamento == 1) {
        return valor * 0.90f;
    }
    return valor;
}

float calculaTroco(float total, float pago) {
    return pago - total;
}

int main(void) {
    float preco, pago, subtotal, total, troco;
    int quantidade, pagamento;
    scanf("%f %d %d %f", &preco, &quantidade, &pagamento, &pago);
    subtotal = calculaSubtotal(preco, quantidade);
    total = aplicaDesconto(subtotal, pagamento);
    troco = calculaTroco(total, pago);
    printf("Subtotal = %.2f\n", subtotal);
    printf("Total a pagar = %.2f\n", total);
    if (troco < 0.0f) {
        printf("Valor insuficiente. Faltam %.2f\n", -troco);
    } else {
        printf("Troco = %.2f\n", troco);
    }
    return 0;
}
