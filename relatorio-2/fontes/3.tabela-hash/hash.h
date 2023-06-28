#include <stdio.h>
#include <stdlib.h>

#define DOT_HEADER "\
digraph G\n\
{\n\
  rankdir=LR\n\
  node\n\
  [\n\
    fontname=Monospace\n\
    shape=record\n\
    style=filled\n\
    fillcolor=grey\n\
  ];\n"

#define DOT_FOOTER "}\n"

typedef struct list_node{
    int value;
    struct list_node *next;
}NODE;

typedef struct hash{
    NODE **t;
    unsigned int m;
    unsigned int n;
}HASH;

HASH *inicia_hash(HASH **h, int m);
void list_insert(NODE **l, NODE *w);
int f(int value, int m);
void hash_insert(HASH **h, NODE *w);
void rehash(HASH **h);
NODE *node_new(int v);
HASH *inicia_hash(HASH **h, int m);
void liberar_hash(HASH **h);
NODE *search(HASH *h, int value);