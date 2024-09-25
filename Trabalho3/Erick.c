#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[50];
    int ehPasta;  // 1 se for pasta, 0 se for arquivo
    struct Node *primeiroFilho;
    struct Node *proximoIrmao;
    struct Node *pai;
} Node;

// inicializa um novo nó (pasta ou arquivo)

Node* criarNo(const char *nome, int ehPasta) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    strcpy(novoNo->name, nome);
    novoNo->ehPasta = ehPasta;
    novoNo->primeiroFilho = NULL;
    novoNo->proximoIrmao = NULL;
    novoNo->pai = NULL;
    return novoNo;
}

// insere um nó (arquivo ou pasta) na lista de filhos de um diretório pai

void inserirNo(Node *pai, Node *novoNo) {
    if (pai->primeiroFilho == NULL) {
        pai->primeiroFilho = novoNo;
    } else {
        Node *atual = pai->primeiroFilho;
        Node *anterior = NULL;
        // Inserção ordenada lexicograficamente
        while (atual != NULL && strcmp(atual->name, novoNo->name) < 0) {
            anterior = atual;
            atual = atual->proximoIrmao;
        }
        if (anterior == NULL) {
            novoNo->proximoIrmao = pai->primeiroFilho;
            pai->primeiroFilho = novoNo;
        } else {
            novoNo->proximoIrmao = atual;
            anterior->proximoIrmao = novoNo;
        }
    }
    novoNo->pai = pai;
}

// mostra o caminho da pasta corrente

void mostrarCaminho(Node *atual) {
    if (atual->pai != NULL) {
        mostrarCaminho(atual->pai);
        printf("-%s", atual->name);
    }
}

// mostra o conteúdo de uma pasta

void listarDiretorio(Node *atual) {
    if (!atual->ehPasta) {
        printf("comando invalido\n");
        return;
    }
    Node *filho = atual->primeiroFilho;
    while (filho != NULL) {
        if (filho->ehPasta) {
            printf("%s-\n", filho->name);
        } else {
            printf("%s\n", filho->name);
        }
        filho = filho->proximoIrmao;
    }
}

// cria um arquivo

void criarArquivo(Node *atual, const char *nome) {
    inserirNo(atual, criarNo(nome, 0));
}

// cria uma pasta

void criarPasta(Node *atual, const char *nome) {
    inserirNo(atual, criarNo(nome, 1));
}

// muda o diretório corrente

Node* mudarDiretorio(Node *atual, const char *nome) {
    if (strcmp(nome, "..") == 0) {
        return (atual->pai != NULL) ? atual->pai : atual;
    }
    Node *filho = atual->primeiroFilho;
    while (filho != NULL) {
        if (filho->ehPasta && strcmp(filho->name, nome) == 0) {
            return filho;
        }
        filho = filho->proximoIrmao;
    }
    printf("comando invalido\n");
    return atual;
}

// apaga um arquivo ou pasta

void removerNo(Node *atual, const char *nome) {
    Node *filho = atual->primeiroFilho;
    Node *anterior = NULL;

    while (filho != NULL && strcmp(filho->name, nome) != 0) {
        anterior = filho;
        filho = filho->proximoIrmao;
    }

    if (filho == NULL) {
        printf("comando invalido\n");
        return;
    }

    // Se o nó encontrado for uma pasta, apagar seus filhos
    if (filho->ehPasta && filho->primeiroFilho != NULL) {
        printf("comando invalido\n");
        return;
    }

    // Se for o primeiro filho
    if (anterior == NULL) {
        atual->primeiroFilho = filho->proximoIrmao;
    } else {
        anterior->proximoIrmao = filho->proximoIrmao;
    }
    free(filho);
}

void copiarStr(char dest[], char orig[], int ini, int fim){
    int i=0, tam=strlen(orig);
    while(i+ini<tam && i<fim-ini && orig[i+ini] != '\0' && orig[i+ini] != '\n'){
        dest[i] = orig[i+ini];
        i++;
    }
    dest[i] = '\0';
}

int main() {
    Node *raiz = criarNo("", 1); // Raiz sem nome
    Node *atual = raiz;

    char str[20];
    char cmd[10], param[256];
    int i = 1;
    do{
        mostrarCaminho(atual);
        printf("-> ");
        fflush(stdin);
        fgets(str, 20, stdin);
        copiarStr(cmd, str, 0, 2);
        copiarStr(param, str, 3, 13);
        printf("str: %s\ncmd: %s\npar: %s\n\n",str,cmd,param);

        if(strcmp(cmd , "ls") == 0){
            listarDiretorio(atual);
            printf("teste ls\n");
        }
        else if(strcmp(cmd , "ma" ) == 0){
            criarArquivo(atual, param);
            printf("teste ma\n");
        }
        else if(strcmp(cmd , "mp")==0){
            criarPasta(atual, param);
            printf("teste mp\n");
        }
        else if(strcmp(cmd , "cd")== 0){
            atual = mudarDiretorio(atual, param);
        }
        else if(strcmp(cmd , "rm")==0){
            removerNo(atual, param);
        }
        else if(strcmp(cmd , "ex")==0){
            printf("sistema encerrado\n");
            i = 0;
            break;
        }
        else{
            printf("comando invalido\n");
        }

    }while (i==1);

    
    return 0;
}
