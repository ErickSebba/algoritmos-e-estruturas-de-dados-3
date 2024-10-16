#include <stdio.h>
#include <stdlib.h>
#include <string.h>

calculaDijkstra(int qtdnos, int origem, int matrizGrafos[qtdnos][qtdnos],int matrizDijkstra[qtdnos][3]){
    int menor, custo, anterior;
    
    for(int k=0; k<qtdnos; k++){
        if(matrizGrafos[origem][k] != -1){
            matrizDijkstra[k][0] = matrizGrafos[origem][k];
            matrizDijkstra[k][1] = origem;
        }
    }
    
    for(int k=0; k<qtdnos; k++){
        if(matrizDijkstra[k][0]<matrizDijkstra[menor][0] && matrizDijkstra[k][2] == 1){
            menor = k;
        }
    }
    matrizDijkstra[menor][1]= origem;

    

    int qtdnos, origem, destino;
    char resposta;

    printf("informe a quantidade de nos no grafo:");
    scanf("%d", &qtdnos);

    int matrizGrafos[qtdnos][qtdnos];
    int matrizDijsktra[qtdnos][3];//numero de nos x custo[0] e anterior[1] e aberto(1)/fechado(0) [2]

    for(origem = 0; origem  < qtdnos; origem++){
        for(int destino = 0; destino < qtdnos; destino++){
            matrizGrafos[origem][destino] = -1;
            if(origem == destino){
                matrizGrafos[origem][destino] = 0;
            }else{
            printf("mAdj(%d,%d):", origem,destino);
            scanf("%d", &matrizGrafos[origem][destino]);
            }
        }
    }

    printf("\n");

    printf("origem:");
    scanf("%d", &origem);
    printf("\n");

    for(int i=0; i<qtdnos; i++){
        matrizDijsktra[i][0] = -1;
        matrizDijsktra[i][1] = NULL;
        matrizDijsktra[i][2] = 1;
    }
    matrizDijsktra[origem][0] = 0;
    

    calcularDijkstra(qtdnos, origem, matrizGrafos, matrizDijsktra);

    printf("mostrar caminho('s' ou 'n'):");
    scanf("%c", &resposta);
    if(resposta == 's'){
        printf("destino:");
        scanf("%d", &destino);
        printf("\n");
    }
    printf("destino:");
    scanf("%d", &destino);
    printf("\n");

return 0;
}