#include <stdio.h>
#include <string.h>

typedef struct {
    char titulo[100], autor[80];
    int ano, disponivel;
} Livro;

void cadastrar(Livro livros[], int *quantidade);
void listar(Livro livros[], int quantidade);
void buscar(Livro livros[], int quantidade);
void alterarDisponibilidade(Livro livros[], int quantidade, int disponivel);

void cadastrar(Livro livros[], int *quantidade) {
    if (*quantidade == 10) { printf("Limite atingido.\n"); return; }
    Livro *l = &livros[(*quantidade)++];
    scanf(" %99[^\n]", l->titulo); scanf(" %79[^\n]", l->autor);
    scanf("%d", &l->ano); l->disponivel = 1;
}

void listar(Livro livros[], int quantidade) {
    for (int i = 0; i < quantidade; i++)
        printf("%d - %s | %s | %d | %s\n", i, livros[i].titulo, livros[i].autor,
               livros[i].ano, livros[i].disponivel ? "Disponivel" : "Emprestado");
}

void buscar(Livro livros[], int quantidade) {
    char titulo[100]; scanf(" %99[^\n]", titulo);
    for (int i = 0; i < quantidade; i++)
        if (strcmp(titulo, livros[i].titulo) == 0) {
            printf("%s - %s\n", livros[i].titulo, livros[i].disponivel ? "Disponivel" : "Emprestado");
            return;
        }
    printf("Livro nao encontrado.\n");
}

void alterarDisponibilidade(Livro livros[], int quantidade, int disponivel) {
    int indice; scanf("%d", &indice);
    if (indice >= 0 && indice < quantidade) livros[indice].disponivel = disponivel;
    else printf("Livro invalido.\n");
}

int main(void) {
    Livro livros[10]; int quantidade = 0, opcao;
    do {
        printf("1-Cadastrar 2-Listar 3-Buscar 4-Emprestar 5-Devolver 0-Sair\n");
        scanf("%d", &opcao);
        if (opcao == 1) cadastrar(livros, &quantidade);
        else if (opcao == 2) listar(livros, quantidade);
        else if (opcao == 3) buscar(livros, quantidade);
        else if (opcao == 4) alterarDisponibilidade(livros, quantidade, 0);
        else if (opcao == 5) alterarDisponibilidade(livros, quantidade, 1);
    } while (opcao != 0);
    return 0;
}
