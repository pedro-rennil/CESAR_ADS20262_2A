#ifndef PLATAFORMA_H
#define PLATAFORMA_H
// ===================================================================
// Pequena camada de compatibilidade com o runtime do Arduino/ESP32.
//
// O jogo original usa millis() e delay() o tempo inteiro (sao
// funcoes padrao do Arduino). Em vez de reescrever centenas de
// chamadas, este arquivo fornece as mesmas duas funcoes em cima da
// API do Windows - assim a logica portada pode ficar quase identica
// ao original.
// ===================================================================
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdint.h>

// Equivalente ao millis() do Arduino: milissegundos desde que o
// programa comecou (na pratica, desde que o Windows ligou - da no
// mesmo pro jogo, que so usa diferencas entre leituras). Assim como
// o original, o contador e de 32 bits e "da a volta" depois de ~49
// dias; o codigo portado usa subtracao com sinal pra continuar
// funcionando corretamente mesmo quando isso acontece.
static __inline uint32_t millis(void) { return (uint32_t)GetTickCount(); }

// Equivalente ao delay() do Arduino: pausa a thread atual.
static __inline void delay(uint32_t ms) { Sleep(ms); }

#endif
