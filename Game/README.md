# Jogo Pokémon em C (Console)

Um mini-jogo RPG de exploração de mapas criado em linguagem C para o terminal/console. O projeto implementa estruturas de dados complexas, manipulação de arquivos e alocação dinâmica.

## 🛠️ Tecnologias e Conceitos Aplicados
- **Structs e Unions:** Para modelar a base de dados dos Pokémons e seus atributos mutáveis.
- **Ponteiros e Alocação Dinâmica:** Gerenciamento eficiente da memória (`malloc`/`free`) para criar e destruir entidades durante o tempo de execução.
- **Modularização:** Organização rigorosa em arquivos `.c` e `.h` separando a lógica de negócio (Pokémon) da lógica de interface e mundo (Jogo).
- **Recursividade:** Utilizada no algoritmo que varre e cura a equipe do jogador.
- **File I/O (Arquivos Binários):** Serialização versionada de `structs` para persistir posição, vida do time e inventário no sistema de "Save" e "Load".
- **Batalha:** Artes ASCII, menu de ataque/item/fuga e vantagem circular Fogo > Planta > Água > Fogo.
- **Raycasting DDA:** Visualização em primeira pessoa com buffer de tela, FOV, colisão contínua e sombreamento ASCII por distância.
- **Cross-Platform:** Funciona tanto no terminal de sistemas Windows quanto Linux/MacOS (Lida nativamente com o `getch()` sem bibliotecas externas problemáticas).

## 🎮 Como Jogar

1. **W, S** - Avança e recua na direção da câmera.
2. **A, D** - Gira a câmera para a esquerda e para a direita.
3. **Gramas Altas (`"`)** - Ande sobre elas! Existe 20% de chance de iniciar uma batalha.
4. **C** - Cura recursivamente toda sua equipe instantaneamente.
5. **P** - Salva o progresso do jogo no arquivo `savegame.dat`.
6. **Q** - Fecha o jogo.

*(Se você fechar o jogo e abrir novamente, ele lerá o arquivo `savegame.dat` e devolverá seu personagem no lugar exato onde estava).*

## 📁 Estrutura do Projeto

```text
Game/
├── include/
│   ├── jogo.h
│   ├── pokemon.h
│   └── sprites.h
├── src/
│   ├── main.c
│   ├── jogo.c
│   ├── pokemon.c
│   └── sprites.c
├── savegame.dat
└── README.md
```

Os arquivos `.h` ficam em `include/` e as implementações `.c` ficam em `src/`.
O arquivo `savegame.dat` continua na raiz para que o jogo preserve o caminho do Save/Load.

## ⚙️ Como Compilar e Executar

Garanta que você tenha o **GCC** instalado e execute os comandos a partir da pasta raiz `Game`.

### Linux e macOS

```bash
gcc -std=c11 -Wall -Wextra -pedantic -Iinclude src/main.c src/jogo.c src/pokemon.c src/sprites.c -lm -o pokemon_game
./pokemon_game
```

### Windows com GCC/MinGW

No PowerShell ou no CMD:

```powershell
gcc -std=c11 -Wall -Wextra -pedantic -Iinclude src/main.c src/jogo.c src/pokemon.c src/sprites.c -lm -o pokemon_game.exe
.\pokemon_game.exe
```

Se o executável tiver sido gerado sem a extensão `.exe`, use:

```powershell
.\pokemon_game
```