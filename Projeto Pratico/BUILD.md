# Construção: PDV de Mercadinho

Projeto: sistema de PDV em C, executado no terminal e sem persistência em arquivos.

Comando: `gcc -Wall -Wextra -pedantic pdv.c -o pdv.exe`

Origem: direto

1. [x] Estrutura principal e menu — implementada e compilada
2. [x] Cadastro e validações — código repetido, preço negativo e quantidade negativa observados
3. [x] Estoque e consulta — entrada, listagem e código inexistente observados
4. [x] Venda — estoque insuficiente, pagamento insuficiente, baixa e troco observados
5. [x] Relatório — vendas realizadas e produto mais vendido observados
6. [x] Testes e documentação — casos registrados e relatório em Markdown preparado
7. [ ] Aplicação em condição nova — alterar ou validar uma regra adicional

## Checkpoint atual
- Critério: compilar o programa sem erros e avançar pelo menu.
- Tarefa pendente: realizar uma aplicação final em condição nova e revisar o relatório.
- Ajuda já dada: estrutura completa do código, README e plano de construção.
- Arquivos: `pdv.c`, `README.md`, `BUILD.md`

## Evidência e lacunas
- Compilação concluída com GCC e sem avisos relevantes.
- Cadastro válido, consulta inexistente, entrada de estoque, venda, troco e relatório já foram executados.
- Pagamento insuficiente foi rejeitado sem finalizar a venda.
- Estoque insuficiente foi rejeitado sem alterar a quantidade.
- Código repetido foi rejeitado.
- Preço negativo e quantidade negativa foram rejeitados com nova leitura.
- Estoque com quantidade 4 foi destacado como baixo.

## Retomada
- Compilar o programa, executar o cadastro de um produto válido e observar o comportamento.
