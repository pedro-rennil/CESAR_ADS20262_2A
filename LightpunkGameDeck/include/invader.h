#ifndef INVADER_H
#define INVADER_H
#include "tipos.h"

// Modo hibrido "Tetris Invader": as pecas do Tetris caem como blocos
// que voce atira pra derrubar, e a cada poucos niveis uma formacao de
// naves-chefe entra pra lutar. Transcricao direta do original.
void inicia_invader(void);
void invader(Tecla segurada, Tecla nova);

#endif
