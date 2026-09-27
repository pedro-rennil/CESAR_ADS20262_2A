#ifndef TETRIS_H
#define TETRIS_H
#include <stdint.h>
#include <stdbool.h>
#include "tipos.h"
#include "config.h"

// As 7 pecas classicas do Tetris, codificadas como no original: 4
// rotacoes de 4 bits cada (1 = celula ocupada), numa grade 4x4.
extern const uint8_t PECAS[7][4][4];

// Tabuleiro do Tetris (campo[y][x] != 0 => celula ocupada). E lido
// pelo modulo de audio (pilha_alta) porque no original a musica
// tambem reagia a pilha estar alta - o acoplamento ja existia la.
extern uint8_t campo[MATRIX_H][MATRIX_W];
extern uint8_t nivel; // nivel de dificuldade atual (tambem usado pelo Invader p/ escolher a musica)
extern uint16_t linhas, pontos;
extern const uint8_t N_NIVEIS; // quantos niveis de velocidade existem (usado pelo audio.c tambem)

bool pilha_alta(void);

void inicia_jogo(void);
void jogo(Tecla segurada, Tecla nova);

#endif
