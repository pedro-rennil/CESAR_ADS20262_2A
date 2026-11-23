# PDV de Mercadinho

Projeto prático da disciplina PIF em linguagem C. Todos os dados são mantidos apenas durante a execução.

## Compilacao

Com GCC instalado:

```bat
gcc -Wall -Wextra -pedantic pdv.c -o pdv.exe
pdv.exe
```

## Funcionalidades

- Cadastro de até 50 produtos
- Entrada em estoque
- Listagem com alerta abaixo de 5 unidades
- Consulta por código
- Venda com até 20 itens no carrinho
- Cálculo de total e troco
- Relatório do dia
- Validação de entradas e regras de negócio

## Estrutura

`Produto` representa os dados do estoque. `ItemCarrinho` representa cada item de uma venda. `PDV` concentra o estado compartilhado da aplicação.

## Roteiro de testes

| Caso | Dados de entrada | Resultado esperado |
|---|---|---|
| Cadastro válido | Código `101`, nome `Arroz`, preço `3.50`, quantidade `10` | Produto cadastrado |
| Código repetido | Novo produto com código `101` | Mensagem de código já cadastrado |
| Preço negativo | Preço `-2.00` | Preço rejeitado; nova leitura solicitada |
| Quantidade negativa | Quantidade inicial `-4` | Quantidade rejeitada; nova leitura solicitada |
| Código inexistente | Consultar código `999` | Produto não encontrado |
| Estoque insuficiente | Vender `50` unidades do produto `101` | Venda rejeitada sem alterar estoque |
| Pagamento menor | Valor pago `5.00` para total `7.00` | Pagamento rejeitado; nova leitura solicitada |
| Venda válida | Comprar `2` unidades por `R$ 3.50`, pagar `R$ 10.00` | Estoque passa de 10 para 8; troco de `R$ 3.00` |

## Entrega

- Relatório do projeto: [Relatorio_PDV_Mercadinho.md](./Relatorio_PDV_Mercadinho.md)
- Integrante informado no relatório: Pedro Henrique Rennil da Silva Souza
- Papel: implementação, integração e documentação
