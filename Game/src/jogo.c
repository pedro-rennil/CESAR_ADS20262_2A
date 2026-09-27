#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sprites.h"
#include "jogo.h"

#define LARGURA 15
#define ALTURA 10
#define LARGURA_TELA 80
#define ALTURA_TELA 24
#define SAVE_MAGIC 0x504B5347
#define SAVE_VERSION 2
#define PI 3.14159265358979323846

// Variável Global do mapa
char mapa[ALTURA][LARGURA+1] = {
    "###############",
    "#.............#",
    "#..\"\"\"\".......#",
    "#..\"\"\"\".......#",
    "#.............#",
    "#......\"\"\"\"\"..#",
    "#......\"\"\"\"\"..#",
    "#.............#",
    "#.............#",
    "###############"
};

// Limpa a tela dependendo do Sistema Operacional
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Cria um jogador novo com dados base
Jogador* inicializarJogador() {
    Jogador* j = (Jogador*)malloc(sizeof(Jogador));
    j->x = 1.5;
    j->y = 1.5;
    j->angulo = 0.0;
    j->fov = PI / 3.0;
    j->plano_camera_x = 0.0;
    j->plano_camera_y = tan(j->fov / 2.0);
    j->qtd_pokemon = 1;
    j->pocoes = 3;
    
    j->equipe = (Pokemon**)malloc(sizeof(Pokemon*) * j->qtd_pokemon);
    j->equipe[0] = criarPokemon("Charmander", 39, 6, FOGO, 12);
    
    return j;
}

// Libera memória de toda a equipe e do jogador
void destruirJogador(Jogador* j) {
    if(j == NULL) return;
    for (int i = 0; i < j->qtd_pokemon; i++) {
        destruirPokemon(j->equipe[i]);
    }
    free(j->equipe);
    free(j);
}

static char sombraParede(double distancia) {
    if (distancia < 1.5) return '#';
    if (distancia < 3.0) return 'O';
    if (distancia < 6.0) return 'o';
    if (distancia < 10.0) return '.';
    return ' ';
}

static void atualizarPlanoCamera(Jogador* j) {
    double comprimento = tan(j->fov / 2.0);
    j->plano_camera_x = -sin(j->angulo) * comprimento;
    j->plano_camera_y = cos(j->angulo) * comprimento;
}

int moverJogador(Jogador* j, double deslocamento_x, double deslocamento_y) {
    double novo_x = j->x + deslocamento_x;
    double novo_y = j->y + deslocamento_y;
    int mapa_x = (int)floor(novo_x);
    int mapa_y = (int)floor(novo_y);

    if (mapa_x <= 0 || mapa_x >= LARGURA - 1 ||
        mapa_y <= 0 || mapa_y >= ALTURA - 1 || mapa[mapa_y][mapa_x] == '#') {
        return 0;
    }

    j->x = novo_x;
    j->y = novo_y;
    return 1;
}

void desenharMapa(Jogador* j) {
    char buffer[ALTURA_TELA][LARGURA_TELA + 1];

    atualizarPlanoCamera(j);
    for (int y = 0; y < ALTURA_TELA; y++) {
        for (int x = 0; x < LARGURA_TELA; x++) {
            buffer[y][x] = y < ALTURA_TELA / 2 ? ' ' : '.';
        }
        buffer[y][LARGURA_TELA] = '\0';
    }

    for (int coluna = 0; coluna < LARGURA_TELA; coluna++) {
        double camera_x = 2.0 * coluna / LARGURA_TELA - 1.0;
        double raio_x = cos(j->angulo) + j->plano_camera_x * camera_x;
        double raio_y = sin(j->angulo) + j->plano_camera_y * camera_x;
        int mapa_x = (int)floor(j->x);
        int mapa_y = (int)floor(j->y);
        int passo_x;
        int passo_y;
        int lado = 0;
        double delta_x = raio_x == 0.0 ? 1e30 : fabs(1.0 / raio_x);
        double delta_y = raio_y == 0.0 ? 1e30 : fabs(1.0 / raio_y);
        double distancia_lado_x;
        double distancia_lado_y;
        int atingiu_parede = 0;

        if (raio_x < 0) {
            passo_x = -1;
            distancia_lado_x = (j->x - mapa_x) * delta_x;
        } else {
            passo_x = 1;
            distancia_lado_x = (mapa_x + 1.0 - j->x) * delta_x;
        }
        if (raio_y < 0) {
            passo_y = -1;
            distancia_lado_y = (j->y - mapa_y) * delta_y;
        } else {
            passo_y = 1;
            distancia_lado_y = (mapa_y + 1.0 - j->y) * delta_y;
        }

        while (!atingiu_parede) {
            if (distancia_lado_x < distancia_lado_y) {
                distancia_lado_x += delta_x;
                mapa_x += passo_x;
                lado = 0;
            } else {
                distancia_lado_y += delta_y;
                mapa_y += passo_y;
                lado = 1;
            }
            if (mapa_x < 0 || mapa_x >= LARGURA || mapa_y < 0 || mapa_y >= ALTURA ||
                mapa[mapa_y][mapa_x] == '#') {
                atingiu_parede = 1;
            }
        }

        double distancia = lado == 0
            ? distancia_lado_x - delta_x
            : distancia_lado_y - delta_y;
        if (distancia < 0.1) distancia = 0.1;
        int altura_parede = (int)(ALTURA_TELA / distancia);
        int inicio = ALTURA_TELA / 2 - altura_parede / 2;
        int fim = ALTURA_TELA / 2 + altura_parede / 2;
        if (inicio < 0) inicio = 0;
        if (fim >= ALTURA_TELA) fim = ALTURA_TELA - 1;

        char caractere = sombraParede(distancia);
        for (int y = inicio; y <= fim; y++) buffer[y][coluna] = caractere;
    }

    limparTela();
    printf("--- POKeMON C | Raycasting ---\n");
    printf("[W/S] Avancar/Recuar | [A/D] Girar | [C] Curar | [P] Salvar | [Q] Sair\n\n");
    for (int y = 0; y < ALTURA_TELA; y++) printf("%s\n", buffer[y]);
    printf("\nHP do %s: %d/%d\n", j->equipe[0]->nome, j->equipe[0]->hp_atual, j->equipe[0]->hp_maximo);
    printf("Pocoes: %d\n", j->pocoes);
}

static int lerOpcaoBatalha(void) {
    int opcao;
    int caractere;
    if (scanf("%d", &opcao) != 1) opcao = 0;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
    return opcao;
}

static int calcularDano(Pokemon* atacante, Pokemon* defensor) {
    float multiplicador = multiplicadorTipo(atacante->tipo, defensor->tipo);
    int dano = (int)(atacante->ataque_base * multiplicador);
    if (dano < 1) dano = 1;
    printf("%s (%s) causou %d de dano", atacante->nome,
           nomeTipo(atacante->tipo), dano);
    if (multiplicador > 1.0f) printf(" - Super efetivo!\n");
    else if (multiplicador < 1.0f) printf(" - Nao muito efetivo...\n");
    else printf(".\n");
    return dano;
}

void iniciarBatalha(Jogador* j) {
    limparTela();
    Pokemon* meu_poke = j->equipe[0];
    Pokemon* inimigo = criarPokemon("Bulbasaur", 40, 5, PLANTA, 10);
    
    printf("Um %s selvagem apareceu!\n\n", inimigo->nome);
    printf("Pressione ENTER para continuar...");
    getchar();

    while (meu_poke->hp_atual > 0 && inimigo->hp_atual > 0) {
        limparTela();
        printf("%s (HP: %d/%d, tipo %s) VS %s (HP: %d/%d, tipo %s)\n\n",
               meu_poke->nome, meu_poke->hp_atual, meu_poke->hp_maximo,
               nomeTipo(meu_poke->tipo), inimigo->nome, inimigo->hp_atual,
               inimigo->hp_maximo, nomeTipo(inimigo->tipo));
        exibirArtePokemon(meu_poke->nome);
        exibirArtePokemon(inimigo->nome);

        printf("\n1. Atacar\n2. Item\n3. Fugir\nEscolha: ");
        switch (lerOpcaoBatalha()) {
            case 1:
                inimigo->hp_atual -= calcularDano(meu_poke, inimigo);
                break;
            case 2:
                if (j->pocoes <= 0) {
                    printf("Voce nao possui pocoes.\n");
                    continue;
                }
                if (meu_poke->hp_atual == meu_poke->hp_maximo) {
                    printf("O HP ja esta cheio.\n");
                    continue;
                }
                j->pocoes--;
                meu_poke->hp_atual += 20;
                if (meu_poke->hp_atual > meu_poke->hp_maximo)
                    meu_poke->hp_atual = meu_poke->hp_maximo;
                printf("Voce usou uma pocao. HP atual: %d/%d\n",
                       meu_poke->hp_atual, meu_poke->hp_maximo);
                break;
            case 3:
                printf("Voce fugiu da batalha.\n");
                destruirPokemon(inimigo);
                printf("Pressione ENTER para voltar ao mapa...");
                getchar();
                return;
            default:
                printf("Opcao invalida.\n");
                continue;
        }
        if (inimigo->hp_atual > 0) {
            meu_poke->hp_atual -= calcularDano(inimigo, meu_poke);
        }
        printf("Pressione ENTER para continuar...");
        getchar();
    }

    if (meu_poke->hp_atual <= 0) printf("\nSeu Pokemon desmaiou!\n");
    else printf("\nVoce venceu a batalha!\n");
    
    destruirPokemon(inimigo);
    printf("Pressione ENTER para voltar ao mapa...");
    getchar();
}

// Serialização: Salva dados no disco
void salvarJogo(Jogador* j, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "wb"); 
    if (arquivo == NULL) {
        printf("\nErro ao salvar o jogo!\n");
        return;
    }
    
    {
        int cabecalho[2] = { SAVE_MAGIC, SAVE_VERSION };
        fwrite(cabecalho, sizeof(int), 2, arquivo);
    }
    fwrite(&(j->x), sizeof(double), 1, arquivo);
    fwrite(&(j->y), sizeof(double), 1, arquivo);
    fwrite(&(j->angulo), sizeof(double), 1, arquivo);
    fwrite(&(j->fov), sizeof(double), 1, arquivo);
    fwrite(&(j->qtd_pokemon), sizeof(int), 1, arquivo);
    fwrite(&(j->pocoes), sizeof(int), 1, arquivo);
    
    for (int i = 0; i < j->qtd_pokemon; i++) {
        fwrite(j->equipe[i], sizeof(Pokemon), 1, arquivo);
    }
    
    fclose(arquivo);
}

// Desserialização: Carrega dados do disco
Jogador* carregarJogo(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        return inicializarJogador(); // Novo jogo se não achar save
    }
    
    Jogador* j = (Jogador*)malloc(sizeof(Jogador));
    {
        int primeiro_valor;
        if (fread(&primeiro_valor, sizeof(int), 1, arquivo) != 1) {
            fclose(arquivo);
            free(j);
            return inicializarJogador();
        }
        if (primeiro_valor == SAVE_MAGIC) {
            int versao;
            fread(&versao, sizeof(int), 1, arquivo);
            if (versao == 1) {
                int x_antigo;
                int y_antigo;
                fread(&x_antigo, sizeof(int), 1, arquivo);
                fread(&y_antigo, sizeof(int), 1, arquivo);
                j->x = x_antigo + 0.5;
                j->y = y_antigo + 0.5;
                j->angulo = 0.0;
                j->fov = PI / 3.0;
                fread(&(j->qtd_pokemon), sizeof(int), 1, arquivo);
                fread(&(j->pocoes), sizeof(int), 1, arquivo);
            } else if (versao == SAVE_VERSION) {
                fread(&(j->x), sizeof(double), 1, arquivo);
                fread(&(j->y), sizeof(double), 1, arquivo);
                fread(&(j->angulo), sizeof(double), 1, arquivo);
                fread(&(j->fov), sizeof(double), 1, arquivo);
                fread(&(j->qtd_pokemon), sizeof(int), 1, arquivo);
                fread(&(j->pocoes), sizeof(int), 1, arquivo);
            } else {
                fclose(arquivo);
                free(j);
                return inicializarJogador();
            }
        } else {
            j->x = primeiro_valor + 0.5;
            {
                int y_antigo;
                fread(&y_antigo, sizeof(int), 1, arquivo);
                j->y = y_antigo + 0.5;
            }
            j->angulo = 0.0;
            j->fov = PI / 3.0;
            fread(&(j->qtd_pokemon), sizeof(int), 1, arquivo);
            j->pocoes = 3;
        }
    }

    atualizarPlanoCamera(j);
    
    j->equipe = (Pokemon**)malloc(sizeof(Pokemon*) * j->qtd_pokemon);
    
    for (int i = 0; i < j->qtd_pokemon; i++) {
        j->equipe[i] = (Pokemon*)malloc(sizeof(Pokemon));
        fread(j->equipe[i], sizeof(Pokemon), 1, arquivo);
    }
    
    fclose(arquivo);
    return j;
}