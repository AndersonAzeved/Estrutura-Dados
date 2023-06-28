#include "hash.h"
#include <time.h>

void list_insert(NODE **l, NODE *w){
    w->next = (*l);
    (*l) = w;
}

int f(int value, int m){
    return value % m;
}

void hash_insert(HASH **h, NODE *w){
    if((*h)->m > (*h)->n){
        list_insert(&(*h)->t[f(w->value, (*h)->m)], w);
        (*h)->n++;
    }else{
        rehash(&(*h));
        list_insert(&(*h)->t[f(w->value, (*h)->m)], w);
        (*h)->n++;
    }
}

void rehash(HASH **h){
   HASH *new = inicia_hash(&new, (((*h)->m) * 2));

   NODE *item, *next;
   
    for(int i = 0; i < (*h)->m; i++){
        item = (*h)->t[i];
        while(item != NULL){
            next = item->next;
            list_insert(&new->t[f(item->value, new->m)], item);
            new->n++;
            item = next;
        }
    }

    free((*h)->t);
    free((*h));
    
    (*h) = new;

}


NODE *node_new(int v){ 
    NODE *w;
 
    w = (NODE*) malloc(sizeof(NODE));
    w->value = v;
    w->next = NULL;
 
    return w;
}


HASH *inicia_hash(HASH **h, int m){
    (*h) = (HASH*) malloc(sizeof(HASH));
    if((*h) != NULL){
        (*h)->m = m;
        (*h)->t = (NODE**) malloc(m * sizeof(NODE*));
        if((*h)->t == NULL){
            free((*h));
            return NULL;
        }
        (*h)->n = 0;
        for(int i = 0; i < (*h)->m; i++)
            (*h)->t[i] = NULL;
    }
    return (*h);
}

void liberar_hash(HASH **h){
    NODE *item, *next;

    for(int i = 0; i < (*h)->m; i++){
        item = (*h)->t[i];
        while(item != NULL){
            next = item->next;
            free(item);
            item = next;
        }      
    }
}

NODE *search(HASH *h, int value){
    int resto = f(value, h->m);
    NODE *aux = h->t[resto];
    while(aux != NULL){
        if(aux->value == value){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

/////////// Implementar para  tabela HASH
void tree_print_dot_body(HASH *h){
    if(h != NULL){  
        NODE *aux;
        for(int i = 0; i < h->m; i++){
            aux = h->t[i];
            printf("  \"%d\" -> \"%d\"", i, i+1); 
            while(aux != NULL){
                printf("  \"%p\"[label=\"{{%d}|{%p}}\"]; ", aux, aux->value, aux->next);
                printf("  \"%p\" -> \"%p\"", aux, aux->next);
                aux = aux->next;
            }
        }
    }
}
 
void tree_print_dot(HASH *h){
    printf("%s", DOT_HEADER);
    tree_print_dot_body(h);
    printf("%s", DOT_FOOTER);
}


////////////


int main(int argc, char **argv){
    HASH *hash = inicia_hash(&hash, 1);
    struct timespec a, b;
    unsigned int t, n;
    int i, *v;

    n = atoi(argv[1]);
    v = (int *) malloc(n * sizeof(int));
    srand(time(NULL));

    // Tempo esperado - Ordem e busca aleatória
    // Tempo de Execução - Próximo a O(1): constante
    //for(i = 0; i < n; i++)
        //hash_insert(&hash, node_new(rand()));

    // Melhor Caso - Ordem crescente ou decrescente de um em um e busca por n, fora do vetor
    // Tempo de Execução - O(1): constante
    for(i = 0; i < n; i++)
        hash_insert(&hash, node_new(i));

    // Pior Caso - Todos os números iguais ou possue o mesmo resto
    // Tempo de Execução - O(n)
    for(i = 0; i < n; i++){
        hash_insert(&hash, node_new(n-1));
    }

    tree_print_dot(hash);

    /*
    clock_gettime(CLOCK_MONOTONIC, &b);
    search(hash, rand()); // Melhor Caso
    //search(hash, n);; // Pior Caso
    clock_gettime(CLOCK_MONOTONIC, &a);

    t = (a.tv_sec * 1e9 + a.tv_nsec) - (b.tv_sec * 1e9 + b.tv_nsec);

    printf("%u\n", t);*/

    liberar_hash(&hash);

    free(v);

    return 0;
}