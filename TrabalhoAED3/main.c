#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Alunos: Erick Sebba, Enrico Soza, Daniel Zamariolli
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
        if (atual->pai == NULL) {
        printf("comando invalido\n");
            return atual;
        }
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

    // Busca o nó que deseja remover
    while (filho != NULL && strcmp(filho->name, nome) != 0) {
        anterior = filho;
        filho = filho->proximoIrmao;
    }

    // Se não encontrar o nó
    if (filho == NULL) {
        printf("comando invalido\n");
        return;
    }

    // Se o nó encontrado for uma pasta e contém filhos, remove recursivamente
    if (filho->ehPasta && filho->primeiroFilho != NULL) {
        Node *filhoAtual = filho->primeiroFilho;
        while (filhoAtual != NULL) {
            Node *temp = filhoAtual;
            filhoAtual = filhoAtual->proximoIrmao;
            removerNo(filho, temp->name); // Chama a remoção recursiva
        }
    }

    // Remoção do nó encontrado
    if (anterior == NULL) {
        atual->primeiroFilho = filho->proximoIrmao; // Se for o primeiro filho
    } else {
        anterior->proximoIrmao = filho->proximoIrmao; // Se não for o primeiro
    }
    
    free(filho); // Libera a memória do nó
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
        printf("->");
        fflush(stdin);
        fgets(str, 20, stdin);
        copiarStr(cmd, str, 0, 2);
        copiarStr(param, str, 3, 13);

        if(strcmp(cmd , "ls") == 0){
            listarDiretorio(atual);

        }
        else if(strcmp(cmd , "ma" ) == 0){
            criarArquivo(atual, param);

        }
        else if(strcmp(cmd , "mp")==0){
            criarPasta(atual, param);

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

