#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[100];
    int is_directory;
    struct Node* parent;
    struct Node* children;
    struct Node* next_sibling;
} Node;

Node* create_node(const char* name, int is_directory) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->is_directory = is_directory;
    node->parent = NULL;
    node->children = NULL;
    node->next_sibling = NULL;
    return node;
}

Node* root;
Node* current_directory;

void print_path(Node* node) {
    if (node == root) {
        printf("->");
        return;
    }
    print_path(node->parent);
    printf("-%s", node->name);
    if (node->is_directory) {
        printf("/");
    }
}

void ls() {
    Node* child = current_directory->children;
    while (child != NULL) {
        printf("%s%s\n", child->name, child->is_directory ? "-" : "");
        child = child->next_sibling;
    }
}

void add_child(Node* parent, Node* child) {
    if (parent->children == NULL) {
        parent->children = child;
    } else {
        Node* current = parent->children;
        Node* previous = NULL;
        while (current != NULL && strcmp(current->name, child->name) < 0) {
            previous = current;
            current = current->next_sibling;
        }
        if (previous == NULL) {
            child->next_sibling = parent->children;
            parent->children = child;
        } else {
            previous->next_sibling = child;
            child->next_sibling = current;
        }
    }
    child->parent = parent;
}

void ma(char* name) {
    Node* new_file = create_node(name, 0);
    add_child(current_directory, new_file);
}

void mp(char* name) {
    Node* new_dir = create_node(name, 1);
    add_child(current_directory, new_dir);
}

void cd(char* name) {
    if (strcmp(name, "..") == 0) {
        if (current_directory->parent != NULL) {
            current_directory = current_directory->parent;
        }
    } else {
        Node* child = current_directory->children;
        while (child != NULL) {
            if (child->is_directory && strcmp(child->name, name) == 0) {
                current_directory = child;
                return;
            }
            child = child->next_sibling;
        }
        printf("comando invalido\n");
    }
}

void rm(char* name) {
    Node* child = current_directory->children;
    Node* previous = NULL;
    while (child != NULL) {
        if (strcmp(child->name, name) == 0) {
            if (previous == NULL) {
                current_directory->children = child->next_sibling;
            } else {
                previous->next_sibling = child->next_sibling;
            }
            if (child->is_directory) {
                while (child->children != NULL) {
                    rm(child->children->name);
                }
            }
            free(child);
            return;
        }
        previous = child;
        child = child->next_sibling;
    }
    printf("comando invalido\n");
}

void run() {
    char command[100];
    while (1) {
        print_path(current_directory);
        printf("-> ");
        scanf("%s", command);
        
        if (strcmp(command, "ls") == 0) {
            ls();
        } else if (strcmp(command, "ma") == 0) {
            char filename[100];
            scanf("%s", filename);
            ma(filename);
        } else if (strcmp(command, "mp") == 0) {
            char dirname[100];
            scanf("%s", dirname);
            mp(dirname);
        } else if (strcmp(command, "cd") == 0) {
            char dirname[100];
            scanf("%s", dirname);
            cd(dirname);
        } else if (strcmp(command, "rm") == 0) {
            char name[100];
            scanf("%s", name);
            rm(name);
        } else if (strcmp(command, "ex") == 0) {
            printf("sistema encerrado\n");
            break;
        } else {
            printf("comando invalido\n");
        }
    }
}

int main() {
    root = create_node("root", 1);
    current_directory = root;

    run();

    return 0;
}

/*
Descrição das Funções:
create_node: Cria um novo nó, que pode ser um diretório ou arquivo.
print_path: Imprime o caminho da pasta corrente até a raiz.
ls: Mostra o conteúdo da pasta corrente, listando os arquivos e subpastas.
add_child: Adiciona um arquivo ou pasta como filho do diretório corrente, garantindo a ordem lexicográfica.
ma: Cria um arquivo na pasta corrente.
mp: Cria uma pasta na pasta corrente.
cd: Navega para uma subpasta ou para o diretório pai.
rm: Remove um arquivo ou pasta (e todo o conteúdo dela, se for o caso).
run: Laço principal que captura e executa os comandos do usuário.
main: Função principal que inicializa o sistema de arquivos e inicia o laço de comandos.
Observações:
A árvore não tem limite de profundidade.
Os arquivos e pastas são armazenados em ordem lexicográfica dentro do diretório.
O programa termina ao receber o comando ex, exibindo "sistema encerrado".
*/
