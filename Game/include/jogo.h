#ifndef JOGO_H
#define JOGO_H

#include "pokemon.h" // Importa as definições do arquivo anterior

// STRUCT: Representa o Jogador e seu estado no mapa
typedef struct {
    double x;
    double y;
    double angulo;
    double fov;
    double plano_camera_x;
    double plano_camera_y;
    Pokemon** equipe; // Ponteiro duplo: um array dinâmico de ponteiros de Pokemon
    int qtd_pokemon;
    int pocoes;
} Jogador;

// Protótipos de Funções
Jogador* inicializarJogador();
void destruirJogador(Jogador* j);
void desenharMapa(Jogador* j);
int moverJogador(Jogador* j, double deslocamento_x, double deslocamento_y);
void iniciarBatalha(Jogador* j);

// Funções de manipulação de arquivo (File I/O)
void salvarJogo(Jogador* j, const char* nome_arquivo);
Jogador* carregarJogo(const char* nome_arquivo);
void limparTela(); // Helper para ser multiplataforma

#endif