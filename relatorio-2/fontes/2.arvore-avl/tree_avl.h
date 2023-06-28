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

struct tree_node{
    int value;
    struct tree_node *lchild;
    struct tree_node *rchild;
    unsigned int h;
    struct tree_node *parent;
};

int max(int a, int b);
int height_tree(struct tree_node *w);
int cdiff(struct tree_node *w);
struct tree_node *left_rotate(struct tree_node *x);
struct tree_node *right_rotate(struct tree_node *x);
struct tree_node *right_left_rotate(struct tree_node *x);
struct tree_node *left_right_rotate(struct tree_node *x);
void tree_insert(struct tree_node **r, struct tree_node *w);
struct tree_node *balance(struct tree_node *w);
struct tree_node *search(struct tree_node *r, int v);