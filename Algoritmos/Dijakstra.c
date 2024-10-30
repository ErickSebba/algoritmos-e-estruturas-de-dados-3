#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999 // Definindo um valor grande para representar infinito

void calculaDijkstra(int qtdnos, int origem, int matrizGrafos[qtdnos][qtdnos], int matrizDijkstra[qtdnos][3]) {
    for (int i = 0; i < qtdnos; i++) {
        matrizDijkstra[i][0] = INF;  // Custo
        matrizDijkstra[i][1] = -1;   // Anterior
        matrizDijkstra[i][2] = 1;    // Aberto
    }
    matrizDijkstra[origem][0] = 0;  // A distância do nó de origem para si é 0

    for (int i = 0; i < qtdnos; i++) {
        int menor = -1;

        for (int j = 0; j < qtdnos; j++) {
            if (matrizDijkstra[j][2] && (menor == -1 || matrizDijkstra[j][0] < matrizDijkstra[menor][0])) {
                menor = j;
            }
        }

        if (menor == -1) break;  // Se todos os nós já estão fechados, encerra o loop
        matrizDijkstra[menor][2] = 0;  // Fecha o nó encontrado

        for (int k = 0; k < qtdnos; k++) {
            if (matrizGrafos[menor][k] != -1 && matrizDijkstra[k][2]) { // Se existe um caminho e o nó está aberto
                int novaDistancia = matrizDijkstra[menor][0] + matrizGrafos[menor][k];
                if (novaDistancia < matrizDijkstra[k][0]) {
                    matrizDijkstra[k][0] = novaDistancia;
                    matrizDijkstra[k][1] = menor;
                }
            }
        }
    }
}

void mostrarCaminho(int matrizDijkstra[][3], int origem, int destino) {
    if (matrizDijkstra[destino][0] == INF) {
        printf("custo: Inf\nnao existe um caminho entre %d e %d\n", origem + 1, destino + 1);
        return;
    }
    printf("custo: %d\ncaminho: ", matrizDijkstra[destino][0]);

    int caminho[100], tamanho = 0;
    for (int atual = destino; atual != -1; atual = matrizDijkstra[atual][1]) {
        caminho[tamanho++] = atual;
    }

    for (int i = tamanho - 1; i >= 0; i--) {
        printf("%d", caminho[i] + 1);  // Ajuste para exibir nós a partir de 1
        if (i > 0) printf("->");
    }
    printf("\n");
}

int main() {
    int qtdnos, origem, destino;
    char resposta;

    printf("informe a quantidade de nos no grafo: ");
    scanf("%d", &qtdnos);

    int matrizGrafos[qtdnos][qtdnos];
    int matrizDijkstra[qtdnos][3];  // custo[0], anterior[1], aberto(1)/fechado(0) [2]

    for (origem = 0; origem < qtdnos; origem++) {
        for (int destino = 0; destino < qtdnos; destino++) {
            matrizGrafos[origem][destino] = -1;
            if (origem == destino) {
                matrizGrafos[origem][destino] = 0;
            } else {
                printf("mAdj(%d,%d): ", origem + 1, destino + 1);
                scanf("%d", &matrizGrafos[origem][destino]);
            }
        }
    }

    printf("origem: ");
    scanf("%d", &origem);
    origem--;  // Ajuste para índice começando de 0
    calculaDijkstra(qtdnos, origem, matrizGrafos, matrizDijkstra);

    do {
        printf("mostrar caminho ('s' ou 'n'): ");
        scanf(" %c", &resposta);
        if (resposta == 's') {
            printf("destino: ");
            scanf("%d", &destino);
            destino--;  // Ajuste para índice começando de 0
            mostrarCaminho(matrizDijkstra, origem, destino);
        }
    } while (resposta == 's');

    return 0;
}
