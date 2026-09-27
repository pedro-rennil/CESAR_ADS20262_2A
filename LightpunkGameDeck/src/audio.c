#include "audio.h"
#include "ajustes.h" // volumeSfx, volumeMusica
#include "tetris.h"  // nivel, pilha_alta()
#include "plataforma.h"
#include <stdlib.h>

// ===================================================================
// Musica: mesma logica de sequenciamento do original (groove
// procedural por compasso/passo, escolhido pelo nivel atual), so que
// sem o "envelope" de volume (o original desenhava um fade-out de 4
// estagios via PWM; o Beep() do Windows nao tem controle de volume,
// entao a nota so liga e desliga no fim do "gate").
// ===================================================================

static const uint16_t ESCALA_MUSICA[11] = {440, 494, 523, 587, 659, 740, 784, 880, 988, 1047, 1175};
static const uint8_t ESCALA_MUSICA_N = 11;
static const uint8_t PROGRESSAO[4] = {0, 2, 6, 3};

#define B_(g, a) {g, a, 0}
#define L_(g, a) {g, a, 1}
#define R_ {-1, 0, 0}
static const uint8_t MUSICA_PASSOS = 8;
static const PassoMusica GROOVE[3][2][8] = {
    {
        {B_(0, 2), R_, B_(4, 1), L_(0, 1), B_(0, 1), R_, B_(4, 1), L_(2, 1)},
        {B_(0, 2), R_, B_(4, 1), L_(4, 1), B_(0, 1), L_(2, 0), B_(4, 1), L_(0, 1)},
    },
    {
        {B_(0, 2), R_, B_(0, 0), L_(4, 1), B_(4, 1), R_, B_(0, 0), R_},
        {B_(0, 2), R_, B_(0, 0), L_(7, 1), B_(4, 1), L_(4, 0), L_(2, 1), R_},
    },
    {
        {B_(0, 2), B_(0, 0), B_(4, 1), B_(0, 0), B_(0, 2), B_(0, 0), B_(7, 1), B_(4, 0)},
        {B_(0, 2), B_(0, 0), B_(4, 1), L_(7, 1), B_(0, 2), L_(4, 1), L_(2, 1), L_(4, 0)},
    },
};
#undef B_
#undef L_
#undef R_

static const uint16_t MUSICA_PASSO_MS = 280;
static const uint16_t MUSICA_GATE_BAIXO_MS = 230;
static const uint16_t MUSICA_GATE_LEAD_MS = 520;

const uint16_t PENTA[10] = {1047, 1175, 1319, 1568, 1760, 2093, 2349, 2637, 3136, 3520};
const uint16_t ESCALA_MENU[8] = {LA5, B5, C6, D6, E6, F6, G6, LA6};

uint16_t penta_do_nivel(uint8_t n) {
  uint8_t idx = (uint8_t)((uint16_t)n * 9 / (N_NIVEIS - 1));
  return PENTA[idx < 9 ? idx : 9];
}

static bool musicaLigada = false;
static uint8_t musicaPasso = 0;
static uint8_t musicaCompasso = 0;
static uint32_t musicaPassoInicioMs = 0;
static uint16_t musicaGateMs = 0;
static uint32_t musicaNotaInicioMs = 0;

static uint32_t sfxFimMs = 0;

// ===================================================================
// "Mixer": os dois canais logicos (SFX e musica) viram cada um uma
// frequencia alvo (0 = silencio); a thread de audio so toca a de
// maior prioridade (SFX sempre ganha da musica, que e o mesmo
// espirito do "duck" que o original fazia na musica quando um SFX
// disparava).
// ===================================================================
static CRITICAL_SECTION trava;
static volatile uint16_t tomSfxHz = 0;
static volatile uint16_t tomMusicaHz = 0;
static volatile bool audioRodando = false;
static HANDLE threadAudio = NULL;

static DWORD WINAPI thread_audio(LPVOID param) {
  (void)param;
  while (audioRodando) {
    uint16_t hz;
    EnterCriticalSection(&trava);
    hz = tomSfxHz ? tomSfxHz : tomMusicaHz;
    LeaveCriticalSection(&trava);

    if (hz) Beep(hz, 15); // fatia curta: reamostra o alvo a cada 15ms, entao troca de nota "interrompe" a anterior
    else Sleep(15);
  }
  return 0;
}

void audio_iniciar(void) {
  InitializeCriticalSection(&trava);
  audioRodando = true;
  threadAudio = CreateThread(NULL, 0, thread_audio, NULL, 0, NULL);
}

void audio_encerrar(void) {
  audioRodando = false;
  if (threadAudio) {
    WaitForSingleObject(threadAudio, 500);
    CloseHandle(threadAudio);
    threadAudio = NULL;
  }
  DeleteCriticalSection(&trava);
}

// ---- SFX ----
static void toca_sfx_interna(uint16_t hz, uint16_t ms) {
  EnterCriticalSection(&trava);
  tomSfxHz = volumeSfx ? hz : 0;
  LeaveCriticalSection(&trava);
  sfxFimMs = millis() + ms;
}

void toca_sfx(uint16_t hz, uint16_t ms) { toca_sfx_interna(hz, ms); }
void toca_sfx_tique(uint16_t hz, uint16_t ms) { toca_sfx_interna(hz, ms); }
// "suave" no original tocava com metade do duty (mais baixinho); sem controle de
// volume no Beep() do Windows isso nao tem como se manter, entao vira igual ao tique.
void toca_sfx_suave(uint16_t hz, uint16_t ms) { toca_sfx_interna(hz, ms); }

void para_sfx(void) {
  EnterCriticalSection(&trava);
  tomSfxHz = 0;
  LeaveCriticalSection(&trava);
  sfxFimMs = 0;
}

void atualiza_sfx(void) {
  if (sfxFimMs && millis() >= sfxFimMs) para_sfx();
}

// ---- Musica ----
void musica_nota(uint16_t hz) {
  EnterCriticalSection(&trava);
  tomMusicaHz = (hz && volumeMusica) ? hz : 0;
  LeaveCriticalSection(&trava);
  musicaGateMs = 0;
}

static void musica_silencia(void) {
  EnterCriticalSection(&trava);
  tomMusicaHz = 0;
  LeaveCriticalSection(&trava);
  musicaGateMs = 0;
}

static void musica_dispara(uint8_t idx, uint16_t gateMs) {
  if (idx >= ESCALA_MUSICA_N) idx = ESCALA_MUSICA_N - 1;
  EnterCriticalSection(&trava);
  tomMusicaHz = volumeMusica ? ESCALA_MUSICA[idx] : 0;
  LeaveCriticalSection(&trava);
  musicaGateMs = gateMs;
  musicaNotaInicioMs = millis();
}

static void musica_envelope(void) {
  if (!musicaGateMs) return;
  if (millis() - musicaNotaInicioMs >= musicaGateMs) musica_silencia();
}

static uint8_t nivel_da_musica(void) {
  if (pilha_alta()) return 2;
  return (nivel <= 2) ? 0 : (nivel <= 5) ? 1 : 2;
}

static uint8_t indice_absoluto(int8_t grauRelativo) {
  int idx = PROGRESSAO[musicaCompasso % 4] + grauRelativo;
  while (idx >= ESCALA_MUSICA_N) idx -= 7;
  return (uint8_t)idx;
}

static void musica_inicia_passo(void) {
  const PassoMusica *p = &GROOVE[nivel_da_musica()][musicaCompasso & 1][musicaPasso];
  if (p->grau < 0) return; // passo de descanso: deixa a nota anterior decair pelo proprio "gate"
  uint16_t gate = p->lead ? MUSICA_GATE_LEAD_MS : MUSICA_GATE_BAIXO_MS;
  musica_dispara(indice_absoluto(p->grau), gate);
}

void inicia_musica(void) {
  musicaLigada = true;
  musicaPasso = 0;
  musicaCompasso = 0;
  musicaPassoInicioMs = millis();
  musica_inicia_passo();
}

void para_musica(void) {
  musicaLigada = false;
  musica_silencia();
}

void atualiza_musica(void) {
  if (!musicaLigada) return;
  musica_envelope();
  uint32_t agora = millis();
  if (agora - musicaPassoInicioMs >= MUSICA_PASSO_MS) {
    musicaPassoInicioMs = (agora - musicaPassoInicioMs > MUSICA_PASSO_MS + 100u) ? agora : musicaPassoInicioMs + MUSICA_PASSO_MS;
    if (++musicaPasso >= MUSICA_PASSOS) {
      musicaPasso = 0;
      musicaCompasso++;
    }
    musica_inicia_passo();
  }
}

void motivo_tetris(void) {
  static const uint8_t IDX[3] = {0, 4, 7};
  static const uint16_t DUR[3] = {90, 90, 140};
  for (uint8_t i = 0; i < 3; i++) {
    musica_dispara(IDX[i], DUR[i]);
    uint32_t fim = millis() + DUR[i];
    while ((int32_t)(fim - millis()) > 0) {
      musica_envelope();
      atualiza_sfx();
      delay(2);
    }
  }
  musica_silencia();
}

void reforca_silencio(void) {
  static uint32_t ultimo = 0;
  if (millis() - ultimo < 500) return;
  ultimo = millis();
  if (!sfxFimMs) para_sfx();
  if (!musicaLigada && !musicaGateMs) musica_silencia();
}

void espera_ms(uint32_t ms) {
  uint32_t fim = millis() + ms;
  while ((int32_t)(fim - millis()) > 0) {
    atualiza_musica();
    atualiza_sfx();
    delay(2);
  }
}
