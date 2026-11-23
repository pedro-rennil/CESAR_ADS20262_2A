# Relatorio do Projeto - PDV Mercadinho

**Disciplina:** Projeto Integrador Fase 1 (PIF)  
**Linguagem:** C  
**Integrante:** Pedro Henrique Rennil da Silva Souza  
**Projeto:** Sistema de ponto de venda para mercadinho  
**Arquivos principais:** `pdv.c`, `README.md` e `BUILD.md`

---

## 1. Resumo

Este projeto implementa um sistema de ponto de venda (PDV) executado no terminal. A aplicacao permite cadastrar produtos, controlar o estoque, consultar itens, realizar vendas, calcular troco e apresentar um resumo das vendas do dia.

Os dados ficam armazenados em memoria durante a execucao e sao apagados ao encerrar o programa.

## 2. Objetivos

- Aplicar estruturas, vetores, funcoes, controle de fluxo e entrada e saida em C.
- Criar um sistema organizado em modulos.
- Validar dados informados pelo usuario.
- Impedir operacoes que violem regras de estoque e pagamento.
- Facilitar a compra por meio da apresentacao dos produtos disponiveis.
- Produzir um programa que possa ser compilado e executado no ambiente proposto pela disciplina.

## 3. Funcionalidades implementadas

### 3.1 Cadastro de produtos

- Limite de 50 produtos.
- Codigo inteiro positivo.
- Nome com ate 30 caracteres.
- Preco de venda maior ou igual a zero.
- Quantidade inicial maior ou igual a zero.
- Rejeicao de codigo ja cadastrado.

### 3.2 Controle de estoque

- Entrada de unidades para produtos existentes.
- Listagem completa de codigo, nome, preco e quantidade.
- Alerta de estoque baixo quando a quantidade fica abaixo de cinco unidades.
- Consulta de um produto pelo codigo.

### 3.3 Venda

- Listagem dos produtos com estoque disponivel antes da escolha.
- Adicao de ate 20 itens diferentes ao carrinho.
- Validacao da quantidade solicitada.
- Verificacao contra o estoque atual e contra a quantidade ja adicionada ao carrinho.
- Custo calculado pela multiplicacao de quantidade por preco.
- Resumo da compra com subtotais e total geral.
- Exigencia de pagamento igual ou superior ao total.
- Calculo e exibicao do troco.
- Atualizacao do estoque somente depois da confirmacao da venda.

### 3.4 Relatorio do dia

- Quantidade de vendas realizadas.
- Valor total arrecadado.
- Identificacao do produto mais vendido.
- Mensagem informativa quando ainda nao houve vendas.

## 4. Estrutura do codigo

O programa esta concentrado em `pdv.c` e utiliza os seguintes elementos principais:

| Elemento | Funcao |
|---|---|
| `Produto` | Armazena codigo, nome, preco e quantidade em estoque |
| `ItemCarrinho` | Armazena codigo, quantidade e subtotal de um item vendido |
| `PDV` | Centraliza os produtos e os dados acumulados das vendas |
| `lerInteiro` | Le e valida numeros inteiros |
| `lerPreco` | Le e valida valores de preco |
| `lerValorPago` | Exige um pagamento suficiente |
| `buscarProdutoPorCodigo` | Localiza um produto no vetor |
| `listarProdutosDisponiveis` | Exibe somente os produtos com estoque para venda |
| `realizarVenda` | Executa o fluxo completo de venda |
| `mostrarRelatorio` | Calcula e exibe os indicadores do dia |

## 5. Melhorias de entrada e acessibilidade

Antes da versao atual, a conversao de entradas numericas podia aceitar parte de um texto misturado. Por exemplo, uma entrada como `12abc` poderia ser interpretada como o numero `12`.

O programa passou a:

- Ler a entrada como texto.
- Converter com `strtol` para inteiros ou `strtod` para numeros decimais.
- Verificar caracteres adicionais apos a parte numerica.
- Validar limites, numeros negativos e valores nao finitos.
- Solicitar novamente a entrada quando houver erro.

Na tela de venda, o usuario recebe uma lista com os produtos que possuem unidades disponiveis. Essa lista informa codigo, nome, preco e quantidade, reduzindo erros e tornando a escolha mais acessivel.

## 6. Compilacao e execucao

### Windows

```bat
gcc -std=c11 -Wall -Wextra -pedantic pdv.c -o pdv.exe
pdv.exe
```

### Alternativa com terminal

```bat
gcc -Wall -Wextra -pedantic pdv.c -o pdv
pdv
```

No terminal, o usuario navega pelo menu numerico e informa os dados solicitados.

## 7. Plano de testes

| ID | Caso de teste | Entrada | Resultado esperado |
|---|---|---|---|
| T01 | Cadastro valido | Codigo `101`, nome `Arroz`, preco `3.50`, quantidade `10` | Produto cadastrado |
| T02 | Codigo repetido | Outro produto com codigo `101` | Cadastro recusado |
| T03 | Codigo com texto misturado | `12abc` | Entrada rejeitada |
| T04 | Codigo com simbolo ou letra | `@101` ou `abc` | Entrada rejeitada |
| T05 | Preco negativo | `-2.00` | Preco rejeitado e nova leitura solicitada |
| T06 | Quantidade inicial negativa | `-4` | Quantidade rejeitada |
| T07 | Produto inexistente | Codigo `999` | Produto nao encontrado |
| T08 | Estoque insuficiente | Quantidade maior que o estoque | Venda recusada sem alterar estoque |
| T09 | Produto esgotado | Produto com quantidade `0` | Produto nao exibido na lista de venda |
| T10 | Pagamento insuficiente | Valor menor que o total | Pagamento recusado |
| T11 | Venda valida | `2` unidades a `R$ 3.50`, pago `R$ 10.00` | Estoque reduzido e troco de `R$ 3.00` |
| T12 | Estoque baixo | Quantidade menor que `5` | Mensagem de estoque baixo |

## 8. Evidencias de verificacao

A compilacao foi realizada com GCC usando os parametros `-Wall`, `-Wextra` e `-pedantic`. Foram exercitados os fluxos de cadastro valido, codigo invalido, codigo duplicado, estoque insuficiente, pagamento insuficiente, venda valida, troca de produto no carrinho e encerramento do programa.

Durante os testes do fluxo de venda, a aplicacao apresentou a lista de produtos disponiveis antes da solicitacao do codigo. Isso permitiu confirmar que o usuario pode visualizar o estoque para escolher o item.

As validacoes devem ser observadas novamente em ambiente e compilador de destino, pois o comportamento visual pode variar conforme o terminal utilizado.

## 9. Limitacoes

- Os dados nao sao gravados em arquivo ou banco de dados.
- Todos os dados sao perdidos ao encerrar o programa.
- O nome do produto possui limite de 30 caracteres.
- O cadastro aceita no maximo 50 produtos.
- Um carrinho aceita no maximo 20 itens diferentes.
- O relatorio representa apenas as vendas realizadas na execucao atual.

## 10. Trabalhos futuros

- Incluir persistencia em arquivo ou banco de dados.
- Permitir busca de produto por nome.
- Permitir excluir ou editar produtos.
- Adicionar cancelamento de itens do carrinho.
- Gerar comprovante de venda em arquivo.
- Separar o codigo em modulos com arquivos `.h` e `.c`.
- Implementar testes automatizados.

## 11. Conclusao

O sistema atende ao problema proposto ao integrar cadastro, estoque, venda e relatorio em uma aplicacao de terminal. A validacao das entradas numericas reduz a aceitacao indevida de letras e simbolos, enquanto a listagem dos produtos disponiveis melhora a orientacao do usuario durante a venda.

O projeto utiliza recursos fundamentais de linguagem C e mantem uma arquitetura simples, adequada ao nivel e ao objetivo da disciplina.

