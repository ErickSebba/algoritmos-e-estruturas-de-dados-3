# Algoritmos e Estrutura de Dados 3 (AED3)

Estruturas de dados e algoritmos em C, feitos na disciplina de AED3 (2024).

## Estrutura
- `TrabalhoAED3/`: trabalho da disciplina, um simulador de sistema de arquivos em árvore (criar pasta e arquivo, `cd`, `ls`, remover e mostrar o caminho atual).
  - `main.c`: versão final.
  - `versoes/`: versões anteriores e partes do grupo.
- `Arvores/`: árvores AVL, B, binária e rubro-negra.
  - `versoes/`: versão anterior da AVL.
- `Algoritmos/`: Dijkstra.

## Versões do trabalho
| Arquivo | O que é |
|---|---|
| `TrabalhoAED3/main.c` | versão final, com todas as operações |
| `TrabalhoAED3/versoes/Rico.c` | implementação alternativa (agosto de 2024), com comandos `ma`, `mp`, `cd`, `rm` e `ls` |
| `TrabalhoAED3/versoes/Daniel.c` | versão parcial: criação de nós e listagem |
| `TrabalhoAED3/versoes/SepararStrings.c` | teste da função que separa o caminho digitado |
| `Arvores/versoes/ArvoreAVL-2024-08-22.c` | primeira versão da AVL; a final está em `Arvores/ArvoreAVL.c` |

## Como compilar
```
gcc TrabalhoAED3/main.c -o trabalho
./trabalho
```
Os outros arquivos compilam do mesmo jeito: `gcc <arquivo>.c -o programa`.
