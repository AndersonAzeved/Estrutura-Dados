#include "tree_avl.h"
#include <time.h>

int max(int a, int b){
    return (a > b)? a: b;
}

int height_tree(struct tree_node *w){
    if(w == NULL)
        return -1;
    else    
        return w->h;
}

int cdiff(struct tree_node *w){
    if(w)
        return(height_tree(w->lchild) - height_tree(w->rchild));
    else
        return 0;
}

struct tree_node *left_rotate(struct tree_node *x){
    struct tree_node *y, *z;
    y = (struct tree_node *) malloc(sizeof(struct tree_node));
    z = (struct tree_node *) malloc(sizeof(struct tree_node));

    y = x->rchild;
    z = y->lchild;

    y->lchild = x;
    x->rchild = z;

    x->h = max(height_tree(x->lchild),height_tree(x->rchild)) + 1;
    y->h = max(height_tree(y->lchild),height_tree(y->rchild)) + 1;

    return y;

}

struct tree_node *right_rotate(struct tree_node *x){
    struct tree_node *y, *z;
    y = (struct tree_node *) malloc(sizeof(struct tree_node));
    z = (struct tree_node *) malloc(sizeof(struct tree_node));

    y = x->lchild;
    z = y->rchild;

    y->rchild = x;
    x->lchild = z;

    x->h = max(height_tree(x->lchild),height_tree(x->rchild)) + 1;
    y->h = max(height_tree(y->lchild),height_tree(y->rchild)) + 1;

    return y;

}

struct tree_node *right_left_rotate(struct tree_node *x){
    x->rchild = right_rotate(x->rchild);
    return left_rotate(x);
}

struct tree_node *left_right_rotate(struct tree_node *x){
    x->lchild = left_rotate(x->lchild);
    return right_rotate(x);
}


void tree_insert(struct tree_node **r, struct tree_node *w){ // Inserindo a direita ou esquerda
    if((*r) == NULL){
        (*r) = w;
    }else{
        w->parent = *r;
        //w->h = max(height_tree(w->lchild),height_tree(w->rchild)) + 1;
        if((*r)->value < w->value){
            tree_insert(&(*r)->rchild,w);
        }else{
            tree_insert(&(*r)->lchild,w);
        }
    }
    
    (*r)->h = max(height_tree((*r)->lchild),height_tree((*r)->rchild)) + 1;

    (*r) = balance(*r);
    
}

struct tree_node *balance(struct tree_node *w){
    int c = cdiff(w);

    if(c < -1 && cdiff(w->rchild) <= 0)
        w = left_rotate(w);
    
    else if(c > 1 && cdiff(w->lchild) >= 0)
        w = right_rotate(w);
    
    else if(c > 1 && cdiff(w->lchild) < 0)
        w = left_right_rotate(w);
    
    else if(c < -1 && cdiff(w->rchild)> 0)
        w = right_left_rotate(w);
    
    return w;
}


void tree_print(struct tree_node *r){ // Imprimir a árvore
    if (r != NULL){
        tree_print(r->lchild);
        printf("%d - ", r->value);
        tree_print(r->rchild);
    }
}


struct tree_node *tree_new(int v){ // Preenchendo a struct
    struct tree_node *w;
 
    w = (struct tree_node *) malloc(sizeof(struct tree_node));
    w->value = v;
    w->lchild = NULL;
    w->rchild = NULL;
    w->h = 0;
 
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
 
void tree_print_dot(struct tree_node *r){
    printf("%s", DOT_HEADER);
    tree_print_dot_body(r);
    printf("%s", DOT_FOOTER);
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
    struct timespec a, b;
    unsigned int t, n;
    int i, *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));

    /* Preenchendo a árvore */
    /*------------------------------------------------------------------------------*/
    // Tempo esperado - Ordem e busca aleatória
    // Tempo de Execução - Quase O(1): Quase constante
    for(i = 0; i < n; i++)
        tree_insert(&root, tree_new(rand()%100));
    /*----------------------------------------------------------------------------*/

    
    /* Calculando o tempo de execução */
    /*-------------------------------------------------------------------*/
    clock_gettime(CLOCK_MONOTONIC, &b);
    search(root, rand()); // Melhor Caso
    clock_gettime(CLOCK_MONOTONIC, &a);
    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);
    printf("%u\n", t);
    /*-------------------------------------------------------------------*/

    /* Criando o diagrama */
    /*-------------------------------------------------------------------*/
    //tree_print_dot(root);
    /*-------------------------------------------------------------------*/

    free(v);

    return 0;
}