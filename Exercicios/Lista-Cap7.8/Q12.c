#include <stdio.h>

void tabuleiro(char t[3][3]);
int vencedor(char t[3][3]);

void tabuleiro(char t[3][3]) {
    for (int i = 0; i < 3; i++)
        printf(" %c | %c | %c\n%s\n", t[i][0], t[i][1], t[i][2], i < 2 ? "---+---+---" : "");
}

int vencedor(char t[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (t[i][0] != ' ' && t[i][0] == t[i][1] && t[i][1] == t[i][2]) return 1;
        if (t[0][i] != ' ' && t[0][i] == t[1][i] && t[1][i] == t[2][i]) return 1;
    }
    return t[1][1] != ' ' &&
           ((t[0][0] == t[1][1] && t[1][1] == t[2][2]) ||
            (t[0][2] == t[1][1] && t[1][1] == t[2][0]));
}

int main(void) {
    char t[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int linha, coluna, jogadas = 0, valido;
    char jogador = 'X';
    while (jogadas < 9 && !vencedor(t)) {
        do {
            printf("Jogador %c (linha coluna): ", jogador);
            scanf("%d%d", &linha, &coluna);
            valido = linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 &&
                     t[linha][coluna] == ' ';
            if (!valido) printf("Posicao invalida.\n");
        } while (!valido);
        t[linha][coluna] = jogador; jogadas++; tabuleiro(t);
        if (!vencedor(t)) jogador = jogador == 'X' ? 'O' : 'X';
    }
    printf("%s\n", vencedor(t) ? "Vencedor encontrado." : "Empate.");
    return 0;
}

