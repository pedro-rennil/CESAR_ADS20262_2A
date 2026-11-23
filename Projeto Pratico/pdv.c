#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#define CAPACIDADE_PRODUTOS 50
#define CAPACIDADE_ITENS_CARRINHO 20
#define TAMANHO_NOME_PRODUTO 31
#define LIMITE_ESTOQUE_BAIXO 5

typedef struct {
    int codigo;
    char nome[TAMANHO_NOME_PRODUTO];
    double preco;
    int quantidade;
} Produto;

typedef struct {
    int codigo;
    int quantidade;
    double subtotal;
} ItemCarrinho;

typedef struct {
    Produto produtos[CAPACIDADE_PRODUTOS];
    int totalProdutos;
    int quantidadeVendidaPorProduto[CAPACIDADE_PRODUTOS];
    int totalVendas;
    double totalArrecadado;
} PDV;

void limparEntrada(void);
int lerInteiro(const char *mensagem, int minimo);
double lerPreco(const char *mensagem);
double lerValorPago(double total);
int buscarProdutoPorCodigo(PDV *pdv, int codigo);
void exibirMenu(void);
void listarProdutosDisponiveis(PDV *pdv);
void cadastrarProduto(PDV *pdv);
void darEntradaEstoque(PDV *pdv);
void listarEstoque(PDV *pdv);
void consultarProduto(PDV *pdv);
void realizarVenda(PDV *pdv);
void mostrarRelatorio(PDV *pdv);

int main(void) {
    PDV pdv;
    int opcao;

    pdv.totalProdutos = 0;
    pdv.totalVendas = 0;
    pdv.totalArrecadado = 0.0;

    for (int i = 0; i < CAPACIDADE_PRODUTOS; i++) {
        pdv.quantidadeVendidaPorProduto[i] = 0;
    }

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao", 1);
        if (feof(stdin)) {
            break;
        }

        switch (opcao) {
            case 1:
                cadastrarProduto(&pdv);
                break;
            case 2:
                darEntradaEstoque(&pdv);
                break;
            case 3:
                listarEstoque(&pdv);
                break;
            case 4:
                consultarProduto(&pdv);
                break;
            case 5:
                realizarVenda(&pdv);
                break;
            case 6:
                mostrarRelatorio(&pdv);
                break;
            case 7:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida. Escolha uma opcao entre 1 e 7.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}

void limparEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

int lerInteiro(const char *mensagem, int minimo) {
    char entrada[64];
    char *fim;
    long valor;

    do {
        printf("%s: ", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            return minimo;
        }

        errno = 0;
        valor = strtol(entrada, &fim, 10);

        if (fim == entrada || errno == ERANGE ||
            valor < INT_MIN || valor > INT_MAX) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            continue;
        }

        while (*fim != '\0' && isspace((unsigned char)*fim)) {
            fim++;
        }
        if (*fim != '\0') {
            printf("Entrada invalida. Digite apenas um numero inteiro.\n");
            continue;
        }

        if (valor < minimo) {
            printf("Entrada invalida. O valor minimo permitido e %d.\n", minimo);
        }
    } while (valor < minimo);

    return (int)valor;
}

double lerPreco(const char *mensagem) {
    char entrada[64];
    char *fim;
    double valor;

    do {
        printf("%s: ", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Entrada invalida. Digite um valor numerico.\n");
            return 0.0;
        }

        errno = 0;
        valor = strtod(entrada, &fim);

        if (fim == entrada || errno == ERANGE || !isfinite(valor)) {
            printf("Entrada invalida. Digite um valor numerico.\n");
            continue;
        }

        while (*fim != '\0' && isspace((unsigned char)*fim)) {
            fim++;
        }
        if (*fim != '\0') {
            printf("Entrada invalida. Digite apenas um valor numerico.\n");
            continue;
        }

        if (valor < 0.0) {
            printf("Entrada invalida. O preco nao pode ser negativo.\n");
        }
    } while (valor < 0.0);

    return valor;
}

double lerValorPago(double total) {
    char entrada[64];
    char *fim;
    double valorPago;

    do {
        printf("Valor pago: R$ ");
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Entrada invalida. Digite um valor numerico.\n");
            return total;
        }

        errno = 0;
        valorPago = strtod(entrada, &fim);

        if (fim == entrada || errno == ERANGE || !isfinite(valorPago)) {
            printf("Entrada invalida. Digite um valor numerico.\n");
            continue;
        }

        while (*fim != '\0' && isspace((unsigned char)*fim)) {
            fim++;
        }
        if (*fim != '\0') {
            printf("Entrada invalida. Digite apenas um valor numerico.\n");
            continue;
        }

        if (valorPago < total) {
            printf("Valor pago insuficiente. O total da compra e R$ %.2lf.\n", total);
        }
    } while (valorPago < total);

    return valorPago;
}

int buscarProdutoPorCodigo(PDV *pdv, int codigo) {
    for (int i = 0; i < pdv->totalProdutos; i++) {
        if (pdv->produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void exibirMenu(void) {
    printf("\n========================================\n");
    printf("          PDV MERCADINHO\n");
    printf("========================================\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Dar entrada em estoque\n");
    printf("3 - Listar estoque\n");
    printf("4 - Consultar produto\n");
    printf("5 - Realizar venda\n");
    printf("6 - Relatorio do dia\n");
    printf("7 - Sair\n");
}

void listarProdutosDisponiveis(PDV *pdv) {
    int encontrados = 0;

    printf("\nProdutos disponiveis para venda:\n");

    for (int i = 0; i < pdv->totalProdutos; i++) {
        if (pdv->produtos[i].quantidade > 0) {
            printf("Codigo: %d | Nome: %s | Preco: R$ %.2lf | Disponivel: %d\n",
                   pdv->produtos[i].codigo,
                   pdv->produtos[i].nome,
                   pdv->produtos[i].preco,
                   pdv->produtos[i].quantidade);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum produto disponivel em estoque.\n");
    }
}

void cadastrarProduto(PDV *pdv) {
    Produto produto;

    if (pdv->totalProdutos >= CAPACIDADE_PRODUTOS) {
        printf("\nNao e possivel cadastrar mais produtos. Capacidade maxima atingida.\n");
        return;
    }

    printf("\n--- Cadastro de produto ---\n");
    produto.codigo = lerInteiro("Codigo do produto", 1);

    if (buscarProdutoPorCodigo(pdv, produto.codigo) != -1) {
        printf("Codigo ja cadastrado. O cadastro nao foi realizado.\n");
        return;
    }

    do {
        printf("Nome do produto (ate %d caracteres): ", TAMANHO_NOME_PRODUTO - 1);
        if (scanf(" %30[^\n]", produto.nome) != 1) {
            if (feof(stdin)) {
                limparEntrada();
                printf("Cadastro cancelado pela entrada.\n");
                return;
            }
            printf("Entrada invalida.\n");
            limparEntrada();
            continue;
        }
        limparEntrada();

        if (strlen(produto.nome) == 0) {
            printf("O nome nao pode ficar vazio.\n");
        }
    } while (strlen(produto.nome) == 0);

    produto.preco = lerPreco("Preco de venda");
    produto.quantidade = lerInteiro("Quantidade inicial em estoque", 0);

    pdv->produtos[pdv->totalProdutos] = produto;
    pdv->quantidadeVendidaPorProduto[pdv->totalProdutos] = 0;
    pdv->totalProdutos++;

    printf("Produto cadastrado com sucesso!\n");
}

void darEntradaEstoque(PDV *pdv) {
    int codigo;
    int quantidade;
    int indice;

    printf("\n--- Entrada em estoque ---\n");
    codigo = lerInteiro("Codigo do produto", 1);
    indice = buscarProdutoPorCodigo(pdv, codigo);

    if (indice == -1) {
        printf("Produto com codigo %d nao encontrado.\n", codigo);
        return;
    }

    quantidade = lerInteiro("Quantidade recebida", 1);
    pdv->produtos[indice].quantidade += quantidade;

    printf("Entrada registrada. Estoque atual: %d unidade(s).\n",
           pdv->produtos[indice].quantidade);
}

void listarEstoque(PDV *pdv) {
    printf("\n--- Estoque ---\n");

    if (pdv->totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < pdv->totalProdutos; i++) {
        printf("Codigo: %d | Nome: %s | Preco: R$ %.2lf | Quantidade: %d",
               pdv->produtos[i].codigo,
               pdv->produtos[i].nome,
               pdv->produtos[i].preco,
               pdv->produtos[i].quantidade);

        if (pdv->produtos[i].quantidade < LIMITE_ESTOQUE_BAIXO) {
            printf(" | ESTOQUE BAIXO");
        }

        printf("\n");
    }
}

void consultarProduto(PDV *pdv) {
    int codigo;
    int indice;

    printf("\n--- Consulta de produto ---\n");
    codigo = lerInteiro("Codigo do produto", 1);
    indice = buscarProdutoPorCodigo(pdv, codigo);

    if (indice == -1) {
        printf("Produto com codigo %d nao encontrado.\n", codigo);
        return;
    }

    printf("Codigo: %d\n", pdv->produtos[indice].codigo);
    printf("Nome: %s\n", pdv->produtos[indice].nome);
    printf("Preco: R$ %.2lf\n", pdv->produtos[indice].preco);
    printf("Quantidade: %d\n", pdv->produtos[indice].quantidade);

    if (pdv->produtos[indice].quantidade < LIMITE_ESTOQUE_BAIXO) {
        printf("Alerta: estoque baixo.\n");
    }
}

void realizarVenda(PDV *pdv) {
    ItemCarrinho carrinho[CAPACIDADE_ITENS_CARRINHO];
    int totalItensCarrinho = 0;
    double totalCompra = 0.0;
    char continuar;
    int produtosDisponiveis = 0;

    printf("\n--- Nova venda ---\n");
    listarProdutosDisponiveis(pdv);

    for (int i = 0; i < pdv->totalProdutos; i++) {
        if (pdv->produtos[i].quantidade > 0) {
            produtosDisponiveis++;
        }
    }

    if (produtosDisponiveis == 0) {
        printf("Venda cancelada. Nao ha produtos em estoque.\n");
        return;
    }

    do {
        if (totalItensCarrinho >= CAPACIDADE_ITENS_CARRINHO) {
            printf("Limite de %d itens diferentes desta compra atingido.\n",
                   CAPACIDADE_ITENS_CARRINHO);
            break;
        }

        int codigo = lerInteiro("Codigo do produto", 1);
        int indice = buscarProdutoPorCodigo(pdv, codigo);

        if (indice == -1) {
            printf("Produto com codigo %d nao encontrado.\n", codigo);
        } else {
            int quantidade = lerInteiro("Quantidade", 1);

            if (quantidade > pdv->produtos[indice].quantidade) {
                printf("Estoque insuficiente. Disponivel: %d unidade(s).\n",
                       pdv->produtos[indice].quantidade);
            } else {
                int indiceCarrinho = -1;

                for (int i = 0; i < totalItensCarrinho; i++) {
                    if (carrinho[i].codigo == codigo) {
                        indiceCarrinho = i;
                        break;
                    }
                }

                if (indiceCarrinho != -1) {
                    int novaQuantidade =
                        carrinho[indiceCarrinho].quantidade + quantidade;

                    if (novaQuantidade > pdv->produtos[indice].quantidade) {
                        printf("Estoque insuficiente para adicionar o item ao carrinho.\n");
                    } else {
                        carrinho[indiceCarrinho].quantidade = novaQuantidade;
                        carrinho[indiceCarrinho].subtotal =
                            novaQuantidade * pdv->produtos[indice].preco;
                        printf("Quantidade adicionada ao carrinho existente.\n");
                    }
                } else {
                    carrinho[totalItensCarrinho].codigo = codigo;
                    carrinho[totalItensCarrinho].quantidade = quantidade;
                    carrinho[totalItensCarrinho].subtotal =
                        quantidade * pdv->produtos[indice].preco;
                    totalItensCarrinho++;
                    printf("Item adicionado ao carrinho.\n");
                }
            }
        }

        if (totalItensCarrinho < CAPACIDADE_ITENS_CARRINHO) {
            printf("Adicionar outro item? (S/N): ");
            if (scanf(" %c", &continuar) != 1) {
                continuar = 'N';
            }
            limparEntrada();
        } else {
            continuar = 'N';
        }
    } while (continuar == 'S' || continuar == 's');

    if (totalItensCarrinho == 0) {
        printf("Venda cancelada. Nenhum item foi adicionado.\n");
        return;
    }

    printf("\n--- Resumo da compra ---\n");
    totalCompra = 0.0;

    for (int i = 0; i < totalItensCarrinho; i++) {
        int indice = buscarProdutoPorCodigo(pdv, carrinho[i].codigo);
        printf("%s | Quantidade: %d | Subtotal: R$ %.2lf\n",
               pdv->produtos[indice].nome,
               carrinho[i].quantidade,
               carrinho[i].subtotal);
        totalCompra += carrinho[i].subtotal;
    }

    printf("TOTAL: R$ %.2lf\n", totalCompra);

    double valorPago = lerValorPago(totalCompra);
    double troco = valorPago - totalCompra;

    for (int i = 0; i < totalItensCarrinho; i++) {
        int indice = buscarProdutoPorCodigo(pdv, carrinho[i].codigo);
        pdv->produtos[indice].quantidade -= carrinho[i].quantidade;
        pdv->quantidadeVendidaPorProduto[indice] += carrinho[i].quantidade;
    }

    pdv->totalVendas++;
    pdv->totalArrecadado += totalCompra;

    printf("Venda finalizada! Troco: R$ %.2lf\n", troco);
}

void mostrarRelatorio(PDV *pdv) {
    int indiceMaisVendido = -1;
    int maiorQuantidade = 0;

    printf("\n--- Relatorio do dia ---\n");
    printf("Quantidade de vendas realizadas: %d\n", pdv->totalVendas);
    printf("Valor total arrecadado: R$ %.2lf\n", pdv->totalArrecadado);

    if (pdv->totalVendas == 0) {
        printf("Produto mais vendido: nenhum.\n");
        return;
    }

    for (int i = 0; i < pdv->totalProdutos; i++) {
        if (pdv->quantidadeVendidaPorProduto[i] > maiorQuantidade) {
            maiorQuantidade = pdv->quantidadeVendidaPorProduto[i];
            indiceMaisVendido = i;
        }
    }

    if (indiceMaisVendido == -1) {
        printf("Produto mais vendido: nenhum.\n");
    } else {
        printf("Produto mais vendido: %s (%d unidade(s))\n",
               pdv->produtos[indiceMaisVendido].nome,
               maiorQuantidade);
    }
}
