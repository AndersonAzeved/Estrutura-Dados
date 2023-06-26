#include "tree_avl.h"
#include <time.h>

int max(int a, int b){
    return (a > b)? a: b;
}

int heightTree(struct tree_node *w){
    if(w == NULL)
        return -1;
    else    
        return w->h;
}

int cdiff(struct tree_node *w){
    if(w)
        return(heightTree(w->lchild) - heightTree(w->rchild));
    else
        return 0;
}

struct tree_node *leftRotate(struct tree_node *x){
    struct tree_node *y, *z;
    y = (struct tree_node *) malloc(sizeof(struct tree_node));
    z = (struct tree_node *) malloc(sizeof(struct tree_node));

    y = x->rchild;
    z = y->lchild;

    y->lchild = x;
    x->rchild = z;

    x->h = max(heightTree(x->lchild),heightTree(x->rchild)) + 1;
    y->h = max(heightTree(y->lchild),heightTree(y->rchild)) + 1;

    return y;

}

struct tree_node *rightRotate(struct tree_node *x){
    struct tree_node *y, *z;
    y = (struct tree_node *) malloc(sizeof(struct tree_node));
    z = (struct tree_node *) malloc(sizeof(struct tree_node));

    y = x->lchild;
    z = y->rchild;

    y->rchild = x;
    x->lchild = z;

    x->h = max(heightTree(x->lchild),heightTree(x->rchild)) + 1;
    y->h = max(heightTree(y->lchild),heightTree(y->rchild)) + 1;

    return y;

}

struct tree_node *rightLeftRotate(struct tree_node *x){
    x->rchild = rightRotate(x->rchild);
    return leftRotate(x);
}

struct tree_node *leftRightRotate(struct tree_node *x){
    x->lchild = leftRotate(x->lchild);
    return rightRotate(x);
}


void tree_insert(struct tree_node **r, struct tree_node *w){ // Inserindo a direita ou esquerda
    if((*r) == NULL){
        (*r) = w;
    }else{
        w->parent = *r;
        //w->h = max(heightTree(w->lchild),heightTree(w->rchild)) + 1;
        if((*r)->value < w->value){
            tree_insert(&(*r)->rchild,w);
        }else{
            tree_insert(&(*r)->lchild,w);
        }
    }
    
    (*r)->h = max(heightTree((*r)->lchild),heightTree((*r)->rchild)) + 1;

    (*r) = balance(*r);
    
}

struct tree_node *balance(struct tree_node *w){
    int c = cdiff(w);

    if(c < -1 && cdiff(w->rchild) <= 0)
        w = leftRotate(w);
    
    else if(c > 1 && cdiff(w->lchild) >= 0)
        w = rightRotate(w);
    
    else if(c > 1 && cdiff(w->lchild) < 0)
        w = leftRightRotate(w);
    
    else if(c < -1 && cdiff(w->rchild)> 0)
        w = rightLeftRotate(w);
    
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

    // Tempo esperado - Ordem e busca aleatória
    //for(i = 0; i < n; i++)
        //tree_insert(&root, tree_new(rand()));

    // Pior Caso - Ordem crescente ou decrescente e busca por n, fora do vetor
    for(i = 0; i < n; i++)
        tree_insert(&root, tree_new(i));

    
    clock_gettime(CLOCK_MONOTONIC, &b);
    //search(root, rand()); // Melhor Caso
    search(root, n); // Pior Caso
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);

    free(v);

    return 0;
}