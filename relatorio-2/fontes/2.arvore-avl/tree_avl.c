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
        w->h = max(heightTree(w->lchild),heightTree(w->rchild)) + 1;
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
    
    unsigned int i;
    int n = 15;

    srand(time(NULL));
    

    //  Jeito certo
    
    for(i = 0; i < n; i++){
        tree_insert(&root, tree_new(rand()%100));
    }

    tree_print_dot(root);




    // Testando manualmente
    /*
    int v[n];
    int sort;
    for(i = 0; i < n; i++){
        sort = rand()%100;
        v[i] = sort;
        tree_insert(&root, tree_new(sort));
    }
    printf("Valor da Raiz: %d\n", root->value);
    tree_print(root);
    struct tree_node *r = NULL;
    r = (struct tree_node *) malloc(sizeof(struct tree_node));
    r = search(root,15);
    if(r == NULL)
        printf("\n\nNULL\n\n");
    else
        printf("\n\nBusca Encontrada: %d\n\n", r->value);

    printf("Ordem do sorteio\n");
    for(i = 0; i < n; i++){
        printf("%d,", v[i]);
    }
    printf("\n");

    */

   /*int op;
   
   do{
    printf(""
   "1. Inserir Aleatorio\n"
   "2. Inserir Lista\n"
   "3. Busca\n"
   "0. Sair\n"
   );
   scanf("%d", &op);

   switch (op){
    case 1:
        int v[n];
        int sort;

        for(i = 0; i < n; i++){
            sort = rand()%100;
            v[i] = sort;
            tree_insert(&root, tree_new(sort));
        }
        
        printf("Valor da Raiz: %d\n", root->value);
        tree_print(root);

        printf("Ordem do sorteio\n");
        for(i = 0; i < n; i++){
            printf("%d,", v[i]);
        }
        printf("\n");

        struct tree_node *r = NULL;
        r = (struct tree_node *) malloc(sizeof(struct tree_node));
        r = search(root,15);

        if(r == NULL)
            printf("\n\nNULL\n\n");
        else
            printf("\n\nBusca Encontrada: %d\n\n", r->value);
        break;
    case 3:
        int v[n];
        int sort;

        for(i = 0; i < n; i++){
            sort = rand()%100;
            v[i] = sort;
            tree_insert(&root, tree_new(sort));
        }
        
        printf("Valor da Raiz: %d\n", root->value);
        tree_print(root);

        printf("Ordem do sorteio\n");
        for(i = 0; i < n; i++){
            printf("%d,", v[i]);
        }
        printf("\n");

        struct tree_node *r = NULL;
        r = (struct tree_node *) malloc(sizeof(struct tree_node));
        r = search(root,15);

        if(r == NULL)
            printf("\n\nNULL\n\n");
        else
            printf("\n\nBusca Encontrada: %d\n\n", r->value);
   
   default:
    break;
   }

   } while (op != 0);*/
   
   

    

     
    return 0;
}


// gcc -Wall tree_avl.c; gcc tree_avl.c -o tree_avl; ./tree_avl > tree_avl.dot; dot -Tpng tree_avl.dot -o tree_avl.png



/*
int cdiff(struct tree_node *node){
    int max = max(node->lchild->h, node->rchild->h);
    int min = min(node->lchild->h, node->rchild->h);
    return max - min;
}
int case(struct tree_node *node){
    if(leftH > rightH + 1){
        int lLeftH;
        int lRightH;
        lLeftH = w->lchild->lchild->h;
        lRightH = w->lchild->rchild->h;

        if(lLeftH >= lRightH)
            return rightRotate(w);
        else 
            leftRightRotate(w);
    }
}

void balance2(struct tree_node *node){
    node = node->parent;
    while(node != NULL){
        if(cdiff(node) > 1){
            c = case(node);
        }
    }
}*/


/*

void balance(struct tree_node *w){
    int leftH;
    int rightH;
    
    while(w != NULL){
        heightChild(w);
        leftH = w->lchild->h;
        rightH = w->rchild->h;

        if(leftH > rightH + 1){
            int lLeftH;
            int lRightH;
            lLeftH = w->lchild->lchild->h;
            lRightH = w->lchild->rchild->h;

            if(lLeftH >= lRightH)
                rightRotate(w);
            else 
                leftRightRotate(w);
        }

        if(rightH > leftH + 1){
            int rLeftH;
            int rRightH;
            rLeftH = w->rchild->lchild->h;
            rRightH = w->rchild->rchild->h;

            if(rRightH >= rLeftH)
                return leftRotate(w);
            else  
                return rightLeftRotate(w);
        }
    }
}

void rightRotate(struct tree_node *w){
    struct tree_node *q;
    struct tree_node *temp;
    q = (struct tree_node *) malloc(sizeof(struct tree_node));
    temp = (struct tree_node *) malloc(sizeof(struct tree_node));

    q = w->lchild;
    temp = q->rchild;
    q->rchild = w;
    w->lchild = temp;
    w = q;
}

void leftRotate(struct tree_node *w){
    struct tree_node *q;
    struct tree_node *temp;
    q = (struct tree_node *) malloc(sizeof(struct tree_node));
    temp = (struct tree_node *) malloc(sizeof(struct tree_node));

    q = w->rchild;
    temp = q->lchild;
    q->lchild = w;
    w->rchild = temp;
    w = q;
}

void leftRightRotate(struct tree_node *w){
    leftRotate(w->lchild);
    rightRotate(w);
}

void rightLeftRotate(struct tree_node *w){
    rightRotate(w->rchild);
    leftRotate(w);
}

int heightChild(struct tree_node *w){
    int leftH;
    int rightH;
    leftH = w->lchild->h;
    rightH = w->rchild->h;
    return 1+max(leftH, rightH);
}

*/