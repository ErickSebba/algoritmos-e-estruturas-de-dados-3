#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int valor;
    struct nodo *esq;
    struct nodo *dir;
} Nodo;

Nodo* criarNodo(int v){
    Nodo *p = (Nodo*)malloc(sizeof(Nodo));
    p->valor = v;
    p->esq = NULL;
    p->dir = NULL;
    return p;
}

Nodo* inserirNodo(Nodo *p, int v){
    Nodo *novo = criarNodo(v);
    if(!p)
        return novo;
    else{
        if(v <= p->valor)
            p->esq = inserirNodo(p->esq,v);
        else
            p->dir = inserirNodo(p->dir,v);
        return p;
    }
}

void mostrar(Nodo *p, int nivel){
    int n = nivel;
    if(!p){
        while(n>0){
            printf("   ");
            n--;
        }
        printf("#\n");
    }else{
        while(n>0){
            printf("   ");
            n--;
        }
        printf("%i\n",p->valor);
        nivel++;
        mostrar(p->esq,nivel);
        mostrar(p->dir,nivel);
    }
}

void mostrar2(Nodo *p, int nivel){
    int i;
    if(p){
        mostrar2(p->dir,nivel+1);
        printf("\n");
        for(i=0;i<nivel;i++)
            printf("\t");
        printf("%i \n",p->valor);
        mostrar2(p->esq,nivel+1);
    }
}

Nodo* maiorSubEsq(Nodo *p){
    if(!p){
        return NULL;
    }
        Nodo *aux = p->esq;
        while(aux->dir){
            aux = aux->dir;
        }
        return aux;
}


Nodo* excluirNodo(Nodo *p, int v){
    if(!p){
        return NULL;
        }
    else if(v < p->valor){
        p->esq = excluirNodo(p->esq, v);
        return p;
        }
    else if(v > p->valor){
        p->dir = excluirNodo(p->dir, v);
        return p;
    }else{
        Nodo *aux;
        if(!p->esq && !p->dir){
        free(p);
        return NULL;
        }
    else if(!p->esq){
        aux = p;
        p = p->dir;
        free(aux);
        }
    else if(!p->dir){
        aux = p;
        p = p->esq;
        free(aux);
    }else{
        Nodo *mse = maiorSubEsq(p);
        p->valor = mse->valor;
        p->esq = excluirNodo(p->esq, mse->valor);
        }
        return p;
    }
}

Nodo* busca(Nodo* p, int valor) {
    if (p == NULL || p->valor == valor){
        return p;
    }
        
    if (p ->valor < valor){
        return busca(p->dir, valor); 
    }
    return busca(p->esq, valor);
}

int main(){
    Nodo *raiz = NULL, *aux;
    int v, op;
    op = 1;
    while(op!=0){
        mostrar(raiz, 0);
        printf("Opcoes:\n");
        printf("1 - inserir nodo\n");
        printf("2 - excluir nodo\n");
        printf("3 - buscar\n");
        printf("0 - sair\n");
        printf("op: ");
        scanf("%i", &op);

        switch(op){
        case 1:
            printf("Informe o valor (int): ");
            scanf("%i", &v);
            raiz = inserirNodo(raiz, v);
            break;
        case 2:
            printf("Informe o valor (int): ");
            scanf("%i", &v);
            raiz = excluirNodo(raiz,v);
            break;
        case 3:
            printf("Informe o valor (int): ");
            scanf("%i", &v);
            aux = busca(raiz,v);
            if(!aux){
                 printf("valor nao pertence a arvore\n");
            }
            else{
                printf("valor encontrado\n");
            }
            break;
        case 0:
            printf("saindo...\n");
            break;
        default:
            printf("opcao invalida\n");
        }
        printf("\n\n\n\n\n");
    }
    return 0;
}