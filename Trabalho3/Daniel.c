#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 3 // Grau mínimo para a árvore B

typedef struct Node {
    char names[T - 1][50];
    int ehPasta[T - 1];
    struct Node *filhos[T];
    int numChaves;
    int ehFolha;
} Node;

Node* criarNo(int ehFolha) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->numChaves = 0;
    novoNo->ehFolha = ehFolha;
    for (int i = 0; i < T; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

/*void inserirNo(Node* raiz, const char* nome, int ehPasta) {
    if (raiz->numChaves == T - 1) {
        Node* novoRaiz = criarNo(0);
        novoRaiz->filhos[0] = raiz;
        // Divide o nó raiz
        // Dividir a lógica aqui
    }
    
    // Localizar o nó correto para inserir
    int i = raiz->numChaves - 1;
    while (i >= 0 && strcmp(nome, raiz->names[i]) < 0) {
        raiz->names[i + 1] = raiz->names[i];
        raiz->ehPasta[i + 1] = raiz->ehPasta[i];
        i--;
    }
    raiz->names[i + 1] = strdup(nome);
    raiz->ehPasta[i + 1] = ehPasta;
    raiz->numChaves++;
}*/

// Função para listar diretórios
void listarDiretorio(Node* atual) {
    if (atual->ehFolha) {
        for (int i = 0; i < atual->numChaves; i++) {
            printf("%s%s\n", atual->names[i], atual->ehPasta[i] ? "-" : "");
        }
    } else {
        for (int i = 0; i < atual->numChaves; i++) {
            listarDiretorio(atual->filhos[i]);
            printf("%s%s\n", atual->names[i], atual->ehPasta[i] ? "-" : "");
        }
        listarDiretorio(atual->filhos[atual->numChaves]);
    }
}

// Funções de navegação, criação e remoção devem ser implementadas aqui

int main() {
    Node* raiz = criarNo(1); // Raiz é um nó folha
    char str[256];
    char cmd[10], param[256];
    int i = 1;

    do {
        printf("-> ");
        fflush(stdin);
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%s %s", cmd, param);

        if (strcmp(cmd, "ls") == 0) {
            listarDiretorio(raiz);
        } else if (strcmp(cmd, "ma") == 0) {
            inserirNo(raiz, param, 0); // 0 para arquivo
        } else if (strcmp(cmd, "mp") == 0) {
            inserirNo(raiz, param, 1); // 1 para pasta
        } else if (strcmp(cmd, "ex") == 0) {
            printf("sistema encerrado\n");
            break;
        } else {
            printf("comando invalido\n");
        }
    } while (1);

    return 0;
}