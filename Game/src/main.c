#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "jogo.h"

// Verifica o Sistema Operacional para capturar teclas corretamente
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    int getch(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        return ch;
    }
#endif

int main() {
    srand(time(NULL)); // Inicializa aleatoriedade
    
    // Tenta carregar o save. Se não existir, gera um novo personagem
    Jogador* player = carregarJogo("savegame.dat");
    char movimento;

    while (1) {
        desenharMapa(player);
        movimento = getch(); // Lê do teclado silenciosamente

        // Opções de Menu
        if (movimento == 'p' || movimento == 'P') {
            salvarJogo(player, "savegame.dat");
            printf("\nJogo salvo com sucesso em 'savegame.dat'!\n");
            printf("Pressione qualquer tecla para continuar...");
            getch();
            continue;
        }
        if (movimento == 'q' || movimento == 'Q') {
            printf("\nSaindo do jogo...\n");
            break;
        }
        if (movimento == 'c' || movimento == 'C') {
            curarEquipeRecursivo(player->equipe, player->qtd_pokemon, 0);
            continue;
        }

        // W/S avancam no eixo da camera; A/D apenas giram a visao.
        const double passo = 0.25;
        const double giro = 0.12;
        int moveu = 0;

        if (movimento == 'a' || movimento == 'A') player->angulo -= giro;
        if (movimento == 'd' || movimento == 'D') player->angulo += giro;
        if (movimento == 'w' || movimento == 'W') {
            moveu = moverJogador(player, cos(player->angulo) * passo,
                                 sin(player->angulo) * passo);
        }
        if (movimento == 's' || movimento == 'S') {
            moveu = moverJogador(player, -cos(player->angulo) * passo,
                                 -sin(player->angulo) * passo);
        }

        if (moveu && player->x > 2.0 && player->x < 7.0 &&
            player->y > 1.0 && player->y < 7.0) {
            if (rand() % 100 < 20) {
                iniciarBatalha(player);
            }
        }
    }

    destruirJogador(player);
    return 0;
}