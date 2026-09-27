#include "entrada.h"
#include "config.h"
#include "plataforma.h"

// Ordem de prioridade quando mais de uma tecla estiver pressionada ao
// mesmo tempo (o keypad analogico original so conseguia enxergar uma
// tecla por vez; um teclado de verdade pode ter varias ao mesmo
// tempo, entao precisamos decidir uma prioridade).
static bool tecla_fisica_pressionada(Tecla t) {
  switch (t) {
    case SELECT: return (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0 || (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
    case ESQUERDA: return (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
    case DIREITA: return (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
    case CIMA: return (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
    case BAIXO: return (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
    default: return false;
  }
}

static Tecla classifica(void) {
  static const Tecla ORDEM[5] = {SELECT, ESQUERDA, DIREITA, CIMA, BAIXO};
  for (uint8_t i = 0; i < 5; i++)
    if (tecla_fisica_pressionada(ORDEM[i])) return ORDEM[i];
  return NADA;
}

static Tecla teclaCandidata = NADA, teclaAceita = NADA;
static uint32_t teclaDesde = 0;

Tecla le_tecla_estavel(void) {
  Tecla agora = classifica();
  if (agora != teclaCandidata) {
    teclaCandidata = agora;
    teclaDesde = millis();
  }
  if (teclaCandidata != teclaAceita && millis() - teclaDesde >= KEY_ESTAVEL_MS) teclaAceita = teclaCandidata;
  return teclaAceita;
}

Tecla ressincroniza_teclado(void) {
  teclaCandidata = teclaAceita = classifica();
  teclaDesde = millis();
  return teclaAceita;
}

bool deve_sair(void) { return (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0; }
