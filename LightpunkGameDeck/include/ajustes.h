#ifndef AJUSTES_H
#define AJUSTES_H
#include <stdint.h>
#include "tipos.h"

#define VOLUME_MIN 0
#define VOLUME_MAX 100
#define VOLUME_STEP 5

// Ajustes persistidos (brilho, volumes, paleta) - equivalente ao que
// o original guardava na flash via Preferences. Aqui viram campos
// globais simples, do mesmo jeito que no arquivo original.
extern uint8_t brilhoAtual;
extern uint8_t volumeSfx;
extern uint8_t volumeMusica;
extern uint8_t paletaAtual;

// Cores da paleta atualmente aplicada (trocadas por aplica_paleta).
extern Cor COR_CAINDO, COR_GRID, COR_GAME_OVER, COR_DESTAQUE;
extern Cor COR_GLITCH_A, COR_GLITCH_B, COR_ASSINATURA;
extern Cor COR_TITULO_A, COR_TITULO_B, COR_MENU, COR_PISO;

void aplica_paleta(uint8_t idx);

// Le/grava brilho, volumes e paleta em "ajustes.dat" (equivalente ao
// savegame.dat do jogo Pokemon: struct simples serializada em
// arquivo binario, so que aqui pras preferencias em vez do progresso).
void carrega_ajustes(void);
void salva_ajustes(void);

// Menu de ajustes (estado AJUSTES).
void desenha_ajustes(void);
void comando_ajustes(Tecla t);
void entra_nos_ajustes(void);
void sai_dos_ajustes(void);

#endif
