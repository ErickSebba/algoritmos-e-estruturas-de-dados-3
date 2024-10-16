#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valor;
    struct nodo *esq;
    struct nodo *dir;
    struct nodo *pai;
    int h; // altura do nodo
} Nodo;

Nodo* criarNodo(int v) {
    Nodo *p = (Nodo*)malloc(sizeof(Nodo));
    p->valor = v;
    p->esq = NULL;
    p->dir = NULL;
    p->pai = NULL;
    p->h = 1;
    return p;
}

int altura(Nodo *p) {
    if(p == NULL){
        return 0;
    }
    return p ? p->h : 0;
}

void atualizarAltura(Nodo *p) {
    if (p) {
        p->h = 1 + (altura(p->esq) > altura(p->dir) ? altura(p->esq) : altura(p->dir));
    }
}

int fb(Nodo *p){
    if (p == NULL){
        return 0;
    }
    return altura(p->esq) - altura(p->dir);
}

Nodo* rotDir(Nodo *raiz) {
    Nodo *novaRaiz = raiz->esq;
    raiz->esq = novaRaiz->dir;
    if (novaRaiz->dir) novaRaiz->dir->pai = raiz;
    novaRaiz->dir = raiz;
    novaRaiz->pai = raiz->pai;
    raiz->pai = novaRaiz;

    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

Nodo* rotEsq(Nodo *raiz) {
    Nodo *novaRaiz = raiz->dir;
    raiz->dir = novaRaiz->esq;
    if (novaRaiz->esq) novaRaiz->esq->pai = raiz;
    novaRaiz->esq = raiz;
    novaRaiz->pai = raiz->pai;
    raiz->pai = novaRaiz;

    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

Nodo* rotEsqDir(Nodo *raiz) {
    raiz->esq = rotEsq(raiz->esq);
    return rotDir(raiz);
}

Nodo* rotDirEsq(Nodo *raiz) {
    raiz->dir = rotDir(raiz->dir);
    return rotEsq(raiz);
}

Nodo* balancear(Nodo *raiz) {
    atualizarAltura(raiz);
    int fator = fb(raiz);

    if (fator > 1) {
        if (fb(raiz->esq) >= 0)
            raiz = rotDir(raiz);
        else
            raiz = rotEsqDir(raiz);
    } else if (fator < -1) {
        if (fb(raiz->dir) <= 0)
            raiz = rotEsq(raiz);
        else
            raiz = rotDirEsq(raiz);
    }

    return raiz;
}

Nodo* inserirNodo(Nodo *raiz, int v) {
    if (!raiz) {
        raiz = criarNodo(v);
    } else {
        if (v < raiz->valor) {
            raiz->esq = inserirNodo(raiz->esq, v);
            raiz->esq->pai = raiz;
        } else {
            raiz->dir = inserirNodo(raiz->dir, v);
            raiz->dir->pai = raiz;
        }
    }
    return balancear(raiz);
}

Nodo* excluir(Nodo *raiz, int v) {
    Nodo *aux = NULL;
    if (raiz){
        if (v == raiz->valor){
            if (raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL;
            } else if (raiz->esq == NULL){
                aux = raiz->dir;
                free(raiz);
                return aux;
            } else if (raiz->dir == NULL){
                aux = raiz->esq;
                free(raiz);
                return aux;
            } else{
                aux = raiz->esq;
                while (aux->dir){
                    aux = aux->dir;
                }
                raiz->valor = aux->valor;
                raiz->esq = excluir(raiz->esq, aux->valor);
            }
        } else if(v < raiz->valor) {
            raiz->esq = excluir(raiz->esq, v);
        } else{
            raiz->dir = excluir(raiz->dir, v);
        }

        raiz->h = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));

        raiz = balancear(raiz);
    }
    return raiz;
}

void mostraArvore(Nodo *p, int nivel) {
    int i;
    if (p) {
        mostraArvore(p->dir, nivel + 1);
        printf("\n");
        for (i = 0; i < nivel; i++)
        printf("\t");
        printf("%i [%i|%i]\n", p->valor, p->h, fb(p));
        mostraArvore(p->esq, nivel + 1);
    }
}

Nodo* buscar(Nodo *raiz, int v) {
    if (raiz) {
        if (v == raiz->valor) {
            return raiz;
        } else if (v < raiz->valor) {
            return buscar(raiz->esq, v);
        } else {
            return buscar(raiz->dir, v);
        }
    }
    return NULL;
}

int main() {
    Nodo *raiz = NULL, *aux = NULL;
    int op, v;

    do {
        mostraArvore(raiz, 0);
        printf("\n--------------------------------------------------\n");
        printf("1 - inserir novo nodo\n");
        printf("2 - excluir nodo\n");
        printf("3 - buscar nodo\n");
        printf("0 - sair\n");
        printf("opcao: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
            printf("Informe o valor (int): ");
            scanf("%d", &v);
            raiz = inserirNodo(raiz, v);
            break;
        case 2:
            printf("Informe o valor (int): ");
            scanf("%d", &v);
            raiz = excluir(raiz, v);
            break;
        case 3:
            printf("Informe o valor (int): ");
            scanf("%d", &v);
            aux = buscar(raiz, v);
            if (aux)
                printf("valor encontrado\n");
            else
                printf("valor nao pertence a arvore\n");
            break;
        case 0:
            printf("saindo...\n");
            break;
        default:
            printf("opcao invalida\n");
        }
        printf("\n\n\n");
    } while (op != 0);

    return 0;
}
