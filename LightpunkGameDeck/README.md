# Lightpunk GameDeck - Console Edition

Transcrição para **C puro** do jogo [lightpunk-game-deck](https://github.com/cebola4444/lightpunk-game-deck)
de [@cebolander e @lixofuturista](https://github.com/cebola4444), originalmente escrito em **C++** para
rodar num ESP32 com matriz de LED, keypad analógico e buzzers piezo. Esta versão joga inteiramente no
console/terminal do Windows - sem nenhum hardware externo.

É um Tetris clássico que, a cada tanto, se transforma num modo híbrido "Tetris Invader": as próprias
peças caem como blocos que você atira pra derrubar, e periodicamente uma formação de naves-chefe entra
pra lutar.

## 🎮 Como jogar

- **Setas** - movem a peça (Tetris) ou a nave (Invader)
- **Cima** - hard drop (Tetris) / move a nave pra cima (Invader)
- **ENTER** ou **ESPAÇO** - gira a peça (Tetris) / atira (Invader) - também serve de "SELECT"
- Da tela de espera: qualquer seta começa o **Tetris**; **dois toques curtos de ENTER** começam o
  **Tetris Invader**
- **Segurar ENTER** (~0,8s) na tela de espera abre o **menu de ajustes** (brilho, volume da música,
  volume dos efeitos, paleta de cores); segurar de novo salva e sai. Durante uma partida de Tetris,
  segurar ENTER volta pro menu (no Invader, ENTER é só o gatilho, então esse atalho fica desativado)
- **ESC** - fecha o jogo

## 🛠️ O que mudou do original (e por quê)

O jogo original depende inteiramente de hardware específico de ESP32 (Arduino + FastLED + Preferences +
LEDC/PWM). Como o pedido era rodar no console do notebook, cada peça de hardware foi trocada pelo
equivalente mais direto no PC, mantendo a **lógica do jogo praticamente linha a linha igual ao original**:

| Original (C++/ESP32)                          | Aqui (C/console)                                                        |
| ---------------------------------------------- | ------------------------------------------------------------------------ |
| Matriz 8x16 de LEDs WS2812B (`FastLED`)        | Grade 8x16 de células coloridas via ANSI truecolor (`\x1b[48;2;r;g;bm`)  |
| Keypad analógico de 5 botões (leitura por ADC) | Teclado real (setas + ENTER/ESPAÇO), lido via `GetAsyncKeyState`          |
| 2 buzzers piezo por PWM (`LEDC`, não-bloqueante)| `Beep()` do Windows, rodando numa **thread dedicada** (veja abaixo)      |
| Configurações salvas na flash (`Preferences`)  | Struct simples gravada em `ajustes.dat` (igual ao `savegame.dat` do jogo Pokémon deste repositório) |
| `Serial.println(...)` (debug, só no monitor serial) | Painel de status ao lado da matriz, sempre visível (pontos, nível, vida da nave etc.) |
| `millis()` / `delay()` do Arduino              | Mesmas funções, reimplementadas em cima de `GetTickCount`/`Sleep` (`plataforma.h`) |

### A parte mais delicada: o áudio

No original, o som é PWM controlado por hardware dedicado (`LEDC`), então tocar uma nota **não trava o
resto do jogo** - a música continua enquanto a peça cai. O Windows só oferece `Beep()`, que é **síncrono**
(trava a thread inteira pela duração do som). Tocar cada nota direto no loop principal faria o jogo
inteiro travar por até ~500 ms a cada nota da música - inaceitável.

A solução: `audio.c` sobe uma **thread separada** só pra tocar som. O jogo (thread principal) só decide
"qual frequência devia estar tocando agora" pra cada um dos dois canais lógicos (efeitos e música); a
thread de áudio fica reamostrando esse alvo a cada ~15 ms e chamando `Beep()` em fatias curtas - trocar de
nota "interrompe" a anterior quase instantaneamente, sem travar o jogo.

Duas simplificações assumidas nesse processo (documentadas em `audio.h`):

- O alto-falante do PC só toca **um tom por vez** (efeitos sonoros sempre têm prioridade sobre a música,
  parecido com o "duck" que o original já fazia).
- `Beep()` não tem controle de volume (só liga/desliga na frequência pedida) - os ajustes de volume viraram
  **mudo / não-mudo** em vez de intensidade sonora de verdade.

### Armadilha de C vs. C++

Várias constantes do original são declaradas como `static const` e usadas pra inicializar **outras**
constantes estáticas (ex.: `GLITCH_N_TILES = GLITCH_TILES_X * GLITCH_TILES_Y`). Isso compila liso em C++
(um objeto `const` inicializado por uma expressão constante *é* uma expressão constante), mas o C exige
que o inicializador de um objeto estático seja uma expressão constante *literal* - um `static const`
não conta, não importa a profundidade. A correção foi transformar essas constantes "derivadas" em
`#define` (substituição de texto pura, então continuam válidas onde forem usadas).

## 📁 Estrutura do projeto

```text
LightpunkGameDeck/
├── include/
│   ├── config.h      - tamanho da "matriz" e constantes de tempo
│   ├── tipos.h        - structs/enums compartilhados (tradução direta dos do original)
│   ├── plataforma.h   - millis()/delay() equivalentes ao runtime do Arduino
│   ├── render.h        - framebuffer, desenho, cores, painel de status
│   ├── entrada.h        - leitura do teclado
│   ├── audio.h           - efeitos sonoros e música (thread de Beep())
│   ├── ajustes.h          - paletas de cor, brilho/volume, menu de ajustes, save/load
│   ├── telas.h             - tela de espera, boot, contagem regressiva, game over
│   ├── tetris.h             - tabuleiro, peça atual, pontuação
│   └── invader.h             - modo Tetris Invader
├── src/
│   ├── main.c        - equivalente ao setup()/loop() do original
│   └── *.c            - implementação de cada header acima
├── ajustes.dat        - criado automaticamente na primeira execução
└── README.md
```

## ⚙️ Como compilar e executar

Requer **GCC/MinGW** (mesmo toolchain do jogo Pokémon deste repositório). A partir da pasta
`LightpunkGameDeck`:

```bash
gcc -std=c11 -Wall -Wextra -Iinclude src/*.c -o lightpunk_gamedeck.exe -luser32
.\lightpunk_gamedeck.exe
```

Note que **não usamos `-pedantic`** aqui: várias tabelas (peças do Tetris, bitmaps das telas) usam
literais binários (`0b10100101`) copiados direto do original porque são muito mais legíveis que hex -
só que isso é uma extensão do GCC, então `-pedantic` gera avisos (inofensivos) sobre eles.

Funciona melhor no **Windows Terminal** (cores ANSI de 24 bits com suporte nativo). No `cmd.exe`/
PowerShell antigos pode ser necessário habilitar "Virtual Terminal" no console primeiro.

## ✅ O que foi testado

Compilação limpa (`-Wall -Wextra`, zero avisos) e execução automatizada confirmam que a sequência de
boot, o efeito de glitch, a tela de assinatura, a escala de brilho e o painel de status renderizam
corretamente. A lógica de jogo (rotação com wall-kick, fila de peças do Invader, colisões, ondas,
chefes etc.) foi conferida função a função contra o código original.

O que **não** deu pra testar por aqui: o ambiente onde este projeto foi montado não tem uma área de
trabalho interativa de verdade (sem foco de janela, sem injeção de teclado chegando ao processo), então
a responsividade do teclado em jogo e o som pelo alto-falante físico precisam ser conferidos por você.
Se algo no controle ou no áudio parecer estranho, é o primeiro lugar pra olhar.
