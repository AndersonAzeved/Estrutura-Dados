#include <time.h>
#include "tree.h"


void tree_print(struct tree_node *r){ // Imprimir a árvore
    if (r != NULL){
        tree_print(r->lchild);
        printf("%d\n", r->value);
        tree_print(r->rchild);
    }
}


struct tree_node *tree_new(int v){ // Preenchendo a struct
    struct tree_node *w;
 
    w = (struct tree_node *) malloc(sizeof(struct tree_node));
    w->value = v;
    w->lchild = NULL;
    w->rchild = NULL;
 
    return w;
}


void tree_print_dot_body(struct tree_node *r){
    if (r != NULL)    {
        tree_print_dot_body(r->lchild);
        printf("  \"%p\" [label=\"{%p|%d|{%p|%p}}\"];\n",
               (void *) r,
	       r,
	       r->value,
	       r->lchild,
	       r->rchild);
	if (r->lchild)
            printf("  \"%p\" -> \"%p\";\n", r, r->lchild);
	if (r->rchild)
            printf("  \"%p\" -> \"%p\";\n", r, r->rchild);
        tree_print_dot_body(r->rchild);
    }
}
 
void tree_print_dot(struct tree_node *r)
{
    printf("%s", DOT_HEADER);
    tree_print_dot_body(r);
    printf("%s", DOT_FOOTER);
}


void tree_insert(struct tree_node **r, struct tree_node *w){ // Inserindo a direita ou esquerda
    if((*r) == NULL){
        (*r) = w;
    }else{
        if((*r)->value < w->value){
            tree_insert(&(*r)->rchild,w);
        }else{
            tree_insert(&(*r)->lchild,w);
        }
    }
}


struct tree_node *search(struct tree_node *r, int v){
    if(r != NULL){
        if(r->value == v)
            return r;
        if(r->value < v)
            return search(r->rchild,v);
        return search(r->lchild,v);
    }
    return NULL;
}


int main(int argc, char **argv){
    struct tree_node *root = NULL;
    
    unsigned int i;
    int n = 15;

    srand(time(NULL));

    for(i = 0; i < n; i++){
        tree_insert(&root, tree_new(rand()));
    }


    // Testando manualmente
    /*printf("Valor da Raiz\n");
    printf("%d\n\n", root->value);
    tree_print(root);
    struct tree_node *r = NULL;
    r = (struct tree_node *) malloc(sizeof(struct tree_node));
    r = search(root,15);
    if(r == NULL)
        printf("\n\nNULL\n\n");
    else
        printf("\n\nBusca Encontrada: %d\n\n", r->value);*/



    //  Jeito certo
    tree_print_dot(root);

     
    return 0;
}





//gcc -Wall tree.c; gcc tree.c -o tree; ./tree > tree.dot; dot -Tpng tree.dot -o tree.png