#include <stdio.h>
#include <stdlib.h>

#define DOT_HEADER "\
digraph G\n\
{\n\
  node\n\
  [\n\
    fontname=Monospace\n\
    shape=record\n\
    style=filled\n\
    fillcolor=grey\n\
  ];\n"

#define DOT_FOOTER "}\n"


struct tree_node{ // Criando árvore
    int value;
    struct tree_node *lchild;
    struct tree_node *rchild;
};

struct no{ // Criando o nó
    int value;
    struct no *left;
    struct no *right;
};
 
// Imprime os valores da árvore
// r - o endereço do nó raiz.
void tree_print(struct tree_node *r); 


// Cria e inicializa um novo nó.
// Parâmetros:
// v - o valor a ser armazenado no novo nó.
// Retorna: o endereço do novo nó.
struct tree_node *tree_new(int v);

 
// Insere um novo nó na árvore.
// Parâmetros
// r - o endereço da variável que armazena o endereço da raiz.
// w - o endereço do novo nó.
void tree_insert(struct tree_node **r, struct tree_node *w);



// Imprime uma descrição do gráfico direcionado da árvore no formato DOT.
// Parâmetros:
// r - o endereço do nó raiz.
void tree_print_dot(struct tree_node *r);


struct tree_node *search(struct tree_node *r, int v);