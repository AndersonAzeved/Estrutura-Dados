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

struct list_node{
    int value;
    struct list_node *next;
};

struct hash{
    struct list_node **t;
    unsigned int m;
    unsigned int n;
};




struct hash *inicia_hash(struct hash *t, int m);
void liberar_hash(struct hash *t);
int calc_resto(int value, int m);
int inserir_SemColisão(struct hash *t, struct list_node *l);
int busca_SemColisao(struct hash *t, int value, struct list_node *l);

