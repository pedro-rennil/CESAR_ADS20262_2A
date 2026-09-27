#include "tipos.h"
#include "config.h"
#include "plataforma.h"
#include "render.h"
#include "entrada.h"
#include "audio.h"
#include "ajustes.h"
#include "telas.h"
#include "tetris.h"
#include "invader.h"
#include <stdlib.h>
#include <time.h>

// Dono da variavel de estado global (declarada extern em tipos.h).
Estado estado = PARADA;

static const uint16_t SELECT_LONGO_MS = 800;
static const uint16_t DUPLO_CLIQUE_MS = 350;
static const uint16_t AJUSTE_REPETE_ATRASO_MS = 400;
static const uint16_t AJUSTE_REPETE_INTERVALO_MS = 120;

// Equivalente ao loop() do Arduino original: le o teclado, decide se
// houve uma tecla "nova" (borda de subida) ou "solta" (borda de
// descida) e despacha pro modo atual.
static void loop_principal(void) {
  static Tecla anterior = NADA;
  static uint32_t selectDesde = 0;
  static bool selectLongoDisparado = false;
  static uint32_t ajusteProximoRepete = 0;
  static uint32_t ultimaVolta = 0;
  static uint8_t selectCliques = 0;
  static uint32_t selectCurtoEm = 0;

  atualiza_musica();
  atualiza_sfx();
  reforca_silencio();

  uint32_t agora = millis();
  bool houveBloqueio = (agora - ultimaVolta) > 60;
  ultimaVolta = agora;

  Tecla segurada = le_tecla_estavel();
  if (houveBloqueio) {
    segurada = ressincroniza_teclado();
    anterior = segurada;
    selectDesde = agora;
    selectLongoDisparado = (segurada == SELECT);
  }
  bool borda = (segurada != anterior);
  Tecla nova = borda ? segurada : NADA;
  Tecla solta = borda ? anterior : NADA;
  anterior = segurada;

  if (nova == SELECT) {
    selectDesde = millis();
    selectLongoDisparado = false;
  }
  bool selectCurto = (solta == SELECT && !selectLongoDisparado);

  if (segurada == SELECT && !selectLongoDisparado && estado != INVADER && millis() - selectDesde >= SELECT_LONGO_MS) {
    selectLongoDisparado = true;
    selectCliques = 0;
    if (estado == AJUSTES) sai_dos_ajustes();
    else if (estado == PARADA) entra_nos_ajustes();
    else volta_ao_menu();
    delay(1);
    return;
  }
  if (borda) ajusteProximoRepete = millis() + AJUSTE_REPETE_ATRASO_MS;

  switch (estado) {
    case PARADA:
      atualiza_idle();
      if (nova != NADA && nova != SELECT) {
        selectCliques = 0;
        inicia_jogo();
      } else if (selectCurto) {
        selectCliques++;
        selectCurtoEm = millis();
        if (selectCliques >= 2) {
          selectCliques = 0;
          inicia_invader();
        }
      } else if (selectCliques == 1 && millis() - selectCurtoEm >= DUPLO_CLIQUE_MS) {
        selectCliques = 0;
        inicia_jogo();
      }
      break;

    case AJUSTES:
      if (nova == ESQUERDA || nova == DIREITA || nova == CIMA || nova == BAIXO) {
        comando_ajustes(nova);
      } else if ((segurada == CIMA || segurada == BAIXO) && millis() >= ajusteProximoRepete) {
        ajusteProximoRepete = millis() + AJUSTE_REPETE_INTERVALO_MS;
        comando_ajustes(segurada);
      }
      break;

    case JOGANDO:
      jogo(segurada, nova);
      break;

    case INVADER:
      invader(segurada, nova);
      break;
  }
  delay(1);
}

int main(void) {
  srand((unsigned)time(NULL));

  render_iniciar();
  audio_iniciar();

  carrega_ajustes();
  aplica_paleta(paletaAtual);

  glitch_de_boot();
  assinatura_de_boot();
  fade_out_matriz();
  delay(500);
  inicia_idle_pelo_glitch();

  while (!deve_sair()) loop_principal();

  audio_encerrar();
  render_encerrar();
  return 0;
}
