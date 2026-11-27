# Algoritmos e Estruturas de Dados 3

*Data structures coursework in C: a tree-based file system simulator, an AVL tree, a binary search tree and Dijkstra's shortest path.*

Trabalhos da disciplina de Algoritmos e Estruturas de Dados 3 (UFMT, 2024), em C. O principal é um simulador de sistema de arquivos em árvore, feito em grupo; os outros são estruturas vistas em aula.

## Simulador de sistema de arquivos

[`trabalho-sistema-de-arquivos/main.c`](trabalho-sistema-de-arquivos/main.c) guarda pastas e arquivos numa árvore (primeiro filho e próximo irmão, com ponteiro para o pai). Cada pasta mantém o conteúdo em ordem alfabética. O prompt mostra o caminho da pasta atual.

| Comando | O que faz |
|---|---|
| `mp nome` | cria uma pasta |
| `ma nome` | cria um arquivo |
| `cd nome` / `cd ..` | entra numa pasta / volta para a pasta de cima |
| `ls` | lista o conteúdo da pasta atual (pastas terminam com `-`) |
| `rm nome` | remove um arquivo ou uma pasta |
| `ex` | encerra |

Exemplo de uso (saída real do programa):

```
->mp docs
->ma notas.txt
->cd docs
-docs->ma rel.txt
-docs->mp fotos
-docs->ls
fotos-
rel.txt
-docs->cd ..
->ls
docs-
notas.txt
->rm docs
->ls
notas.txt
->ex
sistema encerrado
```

Os nomes têm até 10 caracteres (o programa lê só esse trecho da linha).

Em [`versoes/`](trabalho-sistema-de-arquivos/versoes/) estão as tentativas anteriores do grupo:

| Arquivo | O que é |
|---|---|
| `versao-alternativa.c` | outra implementação completa, com a descrição de cada função no fim do arquivo |
| `versao-arvore-b-parcial.c` | tentativa com árvore B, incompleta (não compila) |
| `teste_separar_caminho.c` | teste da função que separa o comando do nome |

## Outras estruturas

| Arquivo | O que é |
|---|---|
| [`arvores/arvore_avl.c`](arvores/arvore_avl.c) | árvore AVL com inserção, remoção e busca, mostrando a árvore a cada operação (menu) |
| [`arvores/arvore_binaria.c`](arvores/arvore_binaria.c) | árvore binária de busca com o mesmo menu |
| [`arvores/versoes/arvore_avl_2024-08-22.c`](arvores/versoes/arvore_avl_2024-08-22.c) | primeira versão da AVL |
| [`algoritmos/dijkstra.c`](algoritmos/dijkstra.c) | caminho mínimo de Dijkstra: lê a matriz de adjacência, a origem e o destino e mostra o custo e o caminho |

## Como compilar

```bash
gcc trabalho-sistema-de-arquivos/main.c -o sistema-de-arquivos
./sistema-de-arquivos
```

Os outros programas compilam do mesmo jeito (`gcc arquivo.c -o programa`). Todos foram conferidos com um compilador C recente, exceto `versao-arvore-b-parcial.c`.
